/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 03:00:42 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/16 15:39:07 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

void	execute_command_child(t_minishell *shell, t_ast_node *cmd_node, int input, int output)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = split_cmd(cmd_node->value, " ");
	if (!cmd_args)
		handle_error("Error splitting command", 0, 2);
	cmd_path = get_path(cmd_args[0], getenv("PATH"));
	if (!cmd_path)
		handle_error("command not found", 0, 127);
	if (dup2(input, STDIN_FILENO) == -1 || dup2(output, STDOUT_FILENO) == -1)
		handle_error("Error in dup2", 1, EXIT_FAILURE);
	close(input);
	execve(cmd_path, cmd_args, shell->envp);
	ft_free_arrays(cmd_args);
	handle_error("Error in execve", 1, EXIT_FAILURE);
	free(cmd_path);
}

void	execute_single_cmd(t_minishell *shell, t_ast_node *cmd_node, int input, int output)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	exit_status = 0;
	pid = fork();
	if (pid == -1)
		handle_error("Error in fork", 1, EXIT_FAILURE);
	else if (pid == 0)
		execute_command_child(shell, cmd_node, input, output);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status == EXIT_FAILURE)
				exit(EXIT_FAILURE);
		}
	}
}

void	execute_ast_pipe(t_ast_node *cmd_node, t_minishell *shell)
{
	int		pipes[2];
	int		input_fd;

	input_fd = 0;
	while (cmd_node != NULL && cmd_node->type == AST_PIPE)
	{
		if (pipe(pipes) == -1)
			handle_error("Error creating pipe", 1, EXIT_FAILURE);
		execute_single_cmd(shell, cmd_node->left, input_fd, pipes[1]);
		close(pipes[1]); // cerramos extremo escritura
		if (input_fd != 0)
			close(input_fd);
		input_fd = pipes[0];
		cmd_node = cmd_node->right;
	}
	if (cmd_node != NULL && cmd_node->type == AST_COMMAND)
		execute_single_cmd(shell, cmd_node, input_fd, STDOUT_FILENO);
	if (input_fd != 0)
		close (input_fd);
}
