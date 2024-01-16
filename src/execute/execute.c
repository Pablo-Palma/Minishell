/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:11:06 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/15 15:54:21 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_ast_command(t_minishell *shell, t_ast_node *node)
{
	if (node == NULL || shell == NULL)
	{
		perror("Nodo AST or Shell as NULL");
		return ;
	}
	if (node->type == AST_COMMAND)
		execute_single_command(shell, node->value);
	else if (node->type == AST_REDIRECT_OUT)
		execute_output_redirect(shell, node);
	else
		execute_ast_pipe(shell, node);
}

void	execute_output_redirect(t_minishell *shell, t_ast_node *node)
{
	pid_t	pid;
	int		fd_out;

	pid = fork();
	if (!pid)
	{
		if (ft_strncmp(node->value, ">>", 2) == 0)
			fd_out = open(node->left->value, O_WRONLY | O_CREAT
					| O_APPEND, 0777);
		else
			fd_out = open(node->left->value, O_WRONLY | O_CREAT
					| O_TRUNC, 0777);
		dup2(fd_out, STDOUT_FILENO);
		if (node->right)
			execute_single_command(shell, node->right->value);
		exit(0);
	}
	waitpid(pid, 0, 0);
	return ;
}

void	redirect_stdin(t_minishell *shell)
{
	if (shell->fd_read != STDIN_FILENO)
	{
		dup2(shell->fd_read, STDIN_FILENO);
		close(shell->fd_read);
	}
}

void	execute_single_cmd_process(t_minishell *shell, char **args, char *path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		perror("Fork Error");
	else if (pid == 0)
	{
		redirect_stdin(shell);
		if (execve(path, args, shell->envp) == -1)
		{
			perror("Execve Error");
			exit (EXIT_FAILURE);
		}
	}
	else
	{
		redirect_stdin(shell);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
	}
}

void	execute_single_command(t_minishell *shell, char *value)
{
	char	**args;
	char	*path;

	if (!value || !shell)
		return ;
	args = split_cmd(value, " ");
	if (ft_strncmp(args[0], "./", 2) == 0)
		select_exec(shell, args);
	else if (!handle_special_builtin(shell, args)
		&& !handle_builtin(shell, args))
	{
		path = get_path(args[0], getenv("PATH"));
		if (!path)
			perror("Path Error: ");
		else
		{
			execute_single_cmd_process(shell, args, path);
			free(path);
		}
	}
	ft_free_arrays(args);
}
