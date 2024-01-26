/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 03:00:42 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/25 18:10:48 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_fd(t_minishell *shell)
{
	if (shell->fd_read)
		if (dup2(shell->fd_read, STDIN_FILENO) == -1)
			handle_error("Error in dup2_read", 1, EXIT_FAILURE);
	if ((!shell->last_cmd || shell->output_redirect) && shell->fd_write != 1)
		if (dup2(shell->fd_write, STDOUT_FILENO) == -1)
			handle_error("Error in dup2_write", 1, EXIT_FAILURE);
}

void	execute_command_child(t_minishell *shell, t_ast_node *cmd_node)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = split_cmd(cmd_node->value, " ");
	if (!cmd_args)
		handle_error("Error splitting command", 0, 2);
	cmd_path = get_path(cmd_args[0], my_getenv(shell->envp, "PATH"));
	if (!cmd_path)
		handle_error("command not found", 0, 127);
	handle_fd(shell);
	close(shell->pipes[0]);
	close(shell->pipes[1]);
	execve(cmd_path, cmd_args, shell->envp);
	ft_free_arrays(cmd_args);
	handle_error("Error in execve", 1, EXIT_FAILURE);
	free(cmd_path);
}

void	execute_single_cmd(t_minishell *shell, t_ast_node *cmd_node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		handle_error("Error in fork", 1, EXIT_FAILURE);
	if (!pid)
		execute_command_child(shell, cmd_node);
	if (shell->output_redirect)
		close(shell->fd_write);
	waitpid(pid, &status, 0);
	close(shell->pipes[1]);
	if (shell->fd_read)
		close(shell->fd_read);
	shell->fd_read = shell->pipes[0];
	shell->last_cmd = 1;
	shell->last_exit_status = WEXITSTATUS(status);
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
}

/*void	execute_pipe_cmd(t_minishell *shell, t_ast_node *cmd_node)
{
	if (pipe(shell->pipes) == -1)
		handle_error("Error creating pipe", 1, EXIT_FAILURE);
	shell->fd_write = shell->pipes[1];
	shell->last_cmd = 0;
	if (cmd_node->left)
		execute_multiple_cmd(shell, cmd_node->left);
	if (shell->output_redirect)
	{
		shell->fd_read = 0;
		shell->output_redirect = 0;
	}
	shell->last_cmd = 1;
	if (cmd_node->right)
		execute_multiple_cmd(shell, cmd_node->right);
	close(shell->pipes[0]);
}*/

void	wait_for_commands(pid_t last_pid)
{
	int	status;
	pid_t	pid;

	waitpid(last_pid, &status, 0);
	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if (pid == last_pid)
			break;
	}
}

pid_t	execute_command(t_minishell	*shell, char *cmd_value)
{
	pid_t pid = fork();
	char	**args;
	char	*path;

	if (pid == -1)
		handle_error ("Fork Error", 1, EXIT_FAILURE);
	else if (pid == 0)
	{
		if (shell->fd_read != STDIN_FILENO)
        {
            dup2(shell->fd_read, STDIN_FILENO);
            close(shell->fd_read);
        }
        if (shell->fd_write != STDOUT_FILENO)
        {
            dup2(shell->fd_write, STDOUT_FILENO);
            close(shell->fd_write);
        }
		args = split_cmd(cmd_value, " ");
		path = get_path(args[0], my_getenv(shell->envp, "PATH"));
		execve(path, args, shell->envp);
		handle_error ("Execve Error", 1, EXIT_FAILURE);
	}
	return (pid);
}

void	close_fds(int *pipe_fds, int *fd_in)
{
	if (*pipe_fds != -1)
	{
		close(*pipe_fds);
		*pipe_fds = -1;
	}
	if (*fd_in != 0)
	{
		close(*fd_in);
		*fd_in = 0;
	}
}

void	setup_pipes(t_minishell *shell, t_token *cmd_list)
{
	int	pipe_fds[2];
	int	fd_in = 0;
	pid_t	pid = 0;
	pid_t	last_pid = 0;

	t_token	*current_cmd = cmd_list;
	while (current_cmd != NULL)
	{
		if (current_cmd->next != NULL)
		{
			if (pipe(pipe_fds) == -1)
				handle_error("Error creating pipe", 1, EXIT_FAILURE);
			shell->fd_write = pipe_fds[1];
			shell->fd_read = fd_in;
		}
		else
		{
			shell->fd_write = STDOUT_FILENO;
			shell->fd_read = fd_in;
		}
		pid = execute_command(shell, current_cmd->value);
		last_pid = pid;
		close_fds(&pipe_fds[1], &fd_in);
		if (current_cmd->next != NULL)
			fd_in = pipe_fds[0];
		current_cmd = current_cmd->next;
	}
	if (fd_in != 0)
		close(fd_in);
	wait_for_commands(last_pid);
}

void	create_list(t_minishell *shell, t_ast_node *cmd_node)
{
	t_token	*cmd_list = NULL;
	t_token	*new_token = NULL;
	t_ast_node	*current_node = cmd_node;
	while (current_node)
	{
		if (current_node->left && current_node->left->type == AST_COMMAND)
		{
			new_token = create_token(current_node->left->type, current_node->left->value);
			if (!new_token)
				handle_error("Error creating new token", 1, EXIT_FAILURE);
			add_token_back(&cmd_list, new_token);
		}
		if (current_node->right && current_node->right->type != AST_PIPE)
		{
			new_token = create_token(current_node->right->type, current_node->right->value);
			if (!new_token)
				handle_error("Error creating new token", 1, EXIT_FAILURE);
			add_token_back(&cmd_list, new_token);
		}
		current_node = current_node->right;
	}
	shell->pipe_list = cmd_list;
}

int	execute_multiple_cmd(t_minishell *shell, t_ast_node *cmd_node)
{
	g_sigint_recived = 2;
	if (cmd_node->type == AST_REDIRECT_IN || cmd_node->type == AST_REDIRECT_OUT)
	{
		if (handle_redirect(shell, cmd_node) == -1)
			return (-1);
		if (cmd_node->left)
			execute_single_cmd(shell, cmd_node->left);
	}
	else if (cmd_node->type == AST_COMMAND)
		execute_single_cmd(shell, cmd_node);
	else
	{
		create_list(shell, cmd_node);
		setup_pipes(shell, shell->pipe_list);
	}
	return (1);
}
