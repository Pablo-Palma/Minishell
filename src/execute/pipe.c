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

int count_tokens(t_token *token_list)
{
    int count = 0;
    t_token *current_token = token_list;
    while (current_token != NULL) {
        count++;
        current_token = current_token->next;
    }
    return count;
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
		args = split_cmd(value, " ");
		if (!ft_strncmp(args[0], "cat", 4) && args[1] == NULL)
			pipe_cat(shell);
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
	int	fd_in = 0;
	pid_t	pid = 0;
	pid_t	last_pid = 0;

	t_token	*current_cmd = cmd_list;
	while (current_cmd != NULL)
	{
		if (current_cmd->next != NULL)
		{
			if (pipe(shell->pipes) == -1)
				handle_error("Error creating pipe", 1, EXIT_FAILURE);
			shell->fd_write = shell->pipes[1];
			shell->fd_read = fd_in;
		}
		else
		{
			shell->fd_write = STDOUT_FILENO;
			shell->fd_read = fd_in;
		}
		pid = execute_command(shell, current_cmd->value);
		last_pid = pid;
		close_fds(&shell->pipes[1], &fd_in);
		if (current_cmd->next != NULL && ft_strncmp(current_cmd->value, "cat", 4))
		{
			fd_in = shell->pipes[0];
		}
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
