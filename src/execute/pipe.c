/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 03:00:42 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/20 16:19:36 by jbaeza-c         ###   ########.fr       */
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

	cmd_args = ft_split(cmd_node->value, ' ');
	if (!cmd_args)
		handle_error("Error splitting command", 0, 2);
	cmd_path = get_path(cmd_args[0], getenv("PATH"));
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

void	execute_ast_pipe( t_minishell *shell, t_ast_node *cmd_node)
{
	g_sigint_recived = 2;
	if (cmd_node->type == AST_REDIRECT_IN || cmd_node->type == AST_REDIRECT_OUT)
	{
		handle_redirect(shell, cmd_node);
		if (cmd_node->left)
			execute_single_cmd(shell, cmd_node->left);
	}
	else if (cmd_node->type == AST_COMMAND)
		execute_single_cmd(shell, cmd_node);
	else if (cmd_node->type == AST_PIPE)
	{
		if (pipe(shell->pipes) == -1)
			handle_error("Error creating pipe", 1, EXIT_FAILURE);
		shell->fd_write = shell->pipes[1];
		shell->last_cmd = 0;
		if (cmd_node->left)
			execute_ast_pipe(shell, cmd_node->left);
		if (shell->output_redirect)
		{
			shell->fd_read = 0;
			shell->output_redirect = 0;
		}
		shell->last_cmd = 1;
		if (cmd_node->right)
			execute_ast_pipe(shell, cmd_node->right);
		close(shell->pipes[0]);
	}
}
