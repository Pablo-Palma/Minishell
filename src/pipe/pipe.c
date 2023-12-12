/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 03:00:42 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/13 15:31:42 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd(t_minishell *shell, int pos)
{
	if (pos != shell->number_commands - 1)
		dup2(shell->fd_write, STDOUT_FILENO);
	if (pos)
		dup2(shell->fd_read, STDIN_FILENO);
	close(shell->fd_read);
	close(shell->fd_write);
	execute_command(shell->commands[pos], shell);
}

int	execute_non_pipe_command(t_minishell *shell)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("Fork error");
	if (!pid)
		execute_command(shell->commands[0], shell);
	wait(NULL);
	return (1);
}

int	execute_pipe_command(t_minishell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = -1;
	while( ++i < shell->number_commands)
	{
		if (pipe(fd))
			perror("PIPE ERROR");
		shell->fd_write = fd[1];
		pid = fork();
		if (pid == -1)
			perror("FORK ERROR");
		if (!pid)
			cmd(shell, i);
		waitpid(pid, NULL, 0);
		shell->fd_read = fd[0];
		close(fd[1]);
	}
	return (1);
}