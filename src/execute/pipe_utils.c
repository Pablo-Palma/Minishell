/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 23:36:42 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/29 23:38:17 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	establish_fd(t_minishell *shell, t_ast_node *node, int *fd_in)
{
	if (node->next != NULL)
	{
		if (pipe(shell->pipes) == -1)
			handle_error("Error creating pipe", 1, EXIT_FAILURE);
		if (!shell->output_redirect)
			shell->fd_write = shell->pipes[1];
		shell->fd_read = *fd_in;
	}
	else
	{
		shell->fd_write = STDOUT_FILENO;
		shell->fd_read = *fd_in;
	}
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

int	handle_dup(t_minishell *shell)
{
	if (shell->fd_read != STDIN_FILENO)
    {
    	if (dup2(shell->fd_read, STDIN_FILENO) == -1)
			return (-1);
    	close(shell->fd_read);
    }
   	if (shell->fd_write != STDOUT_FILENO)
    {
    	if (dup2(shell->fd_write, STDOUT_FILENO) == -1)
			return (-1);
    	close(shell->fd_write);
    }
	return (1);
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
