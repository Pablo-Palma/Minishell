/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 03:00:42 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/07 21:42:05 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_minishell *shell, int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	//ft_printf("Primer comando a ejecutar: %s\n", shell->commands[0]);
	execute_command(shell->commands[0], shell);
}

void	parent(t_minishell *shell, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	//ft_printf("Segundo comando a ejecutar: %s\n", shell->commands[1]);
	execute_command(shell->commands[1], shell);
}

int	execute_pipe_command(t_minishell *shell)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
	{
		//ft_printf("Entrando a child process\n");
		child(shell, fd);
	}
	waitpid(pid, NULL, 0);
	//ft_printf("Entrando a parent process\n");
	parent(shell, fd);
	return (1);
}
