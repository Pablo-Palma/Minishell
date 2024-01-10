/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:11:06 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/10 14:07:14 by jbaeza-c         ###   ########.fr       */
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
			fd_out = open(node->left->value, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			fd_out = open(node->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd_out, STDOUT_FILENO);
		execute_single_command(shell, node->right->value);
		exit(0);
	}
	waitpid(pid, 0, 0);
	return;
}

void	execute_single_command(t_minishell *shell, char *value)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**args;

	if (!value || !shell)
		return ;
	args = split_cmd(value, " ");
	if (ft_strncmp(args[0], "./minishell", 11) == 0)
	{
		execute_subshell(shell);
		ft_free_arrays(args);
		return ;
	}
	if (handle_special_builtin(shell, &args[0]))
	{
		return ;
	}
	if (handle_builtin(shell, &args[0]))
	{
		return ;
	}
	path = get_path(args[0], getenv("PATH"));
	if (!path)
		perror("Path Error");
	pid = fork();
	if (pid == -1)
		perror("Fork Error");
	else if (pid == 0)
	{
		if (shell->fd_read != STDIN_FILENO)
		{
			dup2(shell->fd_read, STDIN_FILENO);
			close(shell->fd_read);
		}
		if (execve(path, args, shell->envp) == -1)
		{
			perror("Execve Error");
			exit (EXIT_FAILURE);
		}
	}
	else
	{
		if (shell->fd_read != STDIN_FILENO)
			close(shell->fd_read);
		waitpid(pid, &status, 0);
	}
	free(path);
	ft_free_arrays(args);
}
