/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 03:00:42 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/28 17:50:08 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cat_tokens(t_ast_node *token_list)
{
    t_ast_node	*current_token = token_list;

	if (strcmp(current_token->value, "cat") != 0)
		return (0);
	while (current_token->next != NULL)
		current_token = current_token->next;
	if (strncmp(current_token->value, "cat", 3) != 0)
		return (1);
	return (0);
}

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

void	pipe_cat(t_minishell *shell)
{
	char	*line;
	int		special_pipe[2];

	(void)shell;
	if (pipe(special_pipe) == -1)
		handle_error("Error creating pipe", 1, EXIT_FAILURE);
	line = get_next_line(STDIN_FILENO);
	if (line)
	{
		write (special_pipe[1], line, ft_strlen(line));
		if (line)
			free(line);
	}
	close(special_pipe[1]);
	if (special_pipe[0] != STDIN_FILENO)
	{
		dup2(special_pipe[0], STDIN_FILENO);
		close(special_pipe[0]);
	}
}

pid_t	execute_command(t_minishell	*shell, char *value)
{
	pid_t 	pid;
	char	**args;
	char	*path;

	pid = fork();
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
		args = split_cmd(value, " ");
		if (handle_builtin(shell, args) || special_builtin(shell, args))
			exit(0);
		path = get_path(args[0], my_getenv(shell->envp, "PATH"));
		close(shell->pipes[0]);
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
		*fd_in = STDIN_FILENO;
	}
}

void	setup_pipes(t_minishell *shell, t_ast_node *cmd_list)
{
	int		fd_in = 0;
	pid_t	pid = 0;
	pid_t	last_pid = 0;

	t_ast_node	*current_cmd = cmd_list;
	while (current_cmd != NULL)
	{
		if (current_cmd->next != NULL)
		{
			if (pipe(shell->pipes) == -1)
				handle_error("Error creating pipe", 1, EXIT_FAILURE);
			if (!shell->output_redirect)
				shell->fd_write = shell->pipes[1];
			shell->fd_read = fd_in;
		}
		else
		{
			shell->fd_write = STDOUT_FILENO;
			shell->fd_read = fd_in;
		}
		pid = execute_multiple_cmd(shell, current_cmd);
		last_pid = pid;
		close_fds(&shell->pipes[1], &fd_in);
		if (current_cmd->next != NULL)
			fd_in = shell->pipes[0];
		current_cmd = current_cmd->next;
	}
	if (fd_in != 0)
		close(fd_in);
	wait_for_commands(last_pid);
}

void	create_list(t_minishell *shell, t_ast_node *cmd_node)
{
	t_ast_node	*cmd_list = NULL;
	t_ast_node	*current_node = cmd_node;
	while (current_node && current_node->type == AST_PIPE)
	{
		if (current_node->left && current_node->left->type != AST_PIPE)
			add_ast_back(&cmd_list, current_node->left);
		if (current_node->right && current_node->right->type != AST_PIPE)
			add_ast_back(&cmd_list, current_node->right);
		current_node = current_node->right;
	}
	shell->pipe_list = cmd_list;
}

pid_t	execute_multiple_cmd(t_minishell *shell, t_ast_node *cmd_node)
{
	g_sigint_recived = 2;
	if (cmd_node->type == AST_REDIRECT_IN || cmd_node->type == AST_REDIRECT_OUT)
	{
		if (handle_redirect(shell, cmd_node) == -1)
			return (-1);
		if (cmd_node->left)
			return (execute_multiple_cmd(shell, cmd_node->left));
	}
	else
		return(execute_command(shell, cmd_node->value));
	return (1);
}

void execute_pipe_cmd(t_minishell *shell, t_ast_node *cmd_node)
{
	t_ast_node	*node;

	create_list(shell, cmd_node);
	node = shell->pipe_list;
	while (node)
	{
		printf("Value: %s\n", node->value);
		node = node->next;
	}
	setup_pipes(shell, shell->pipe_list);
}
