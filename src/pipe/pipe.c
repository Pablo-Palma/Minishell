/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 03:00:42 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/08 20:58:33 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd1(t_minishell *shell, int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute_command(shell->commands[0], shell);
}

static void	cmd2(t_minishell *shell, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute_command(shell->commands[1], shell);
}

int	execute_pipe_command(t_minishell *shell)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		return (-1);
	pid1 = fork();
	if (pid1 == -1)
		return (-1);
	if (!pid1)
		cmd1(shell, fd);
	pid2 = fork();
	if (pid2 == -1)
		return (-1);
	if (!pid2)
		cmd2(shell, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (1);
}

int	execute_non_pipe_command(t_minishell *shell)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("Fork error");
	if (!pid)
		execute_command(shell->commands[0], shell);
	waitpid(pid, NULL, 0);
	return (1);
}
