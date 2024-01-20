/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:45:38 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/08 18:51:41 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_subshell(t_minishell *shell, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		 setup_signal_handlers();
		if (execve(args[0], args, shell->og_envp) == -1)
		{
			perror ("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		g_sigint_recived = 0;
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
	}
}

void	execute_program(t_minishell *shell, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == 0)
	{
		if (execve(args[0], args, shell->envp) == -1)
		{
			perror("Execve Error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (shell->fd_read != STDIN_FILENO)
			close(shell->fd_read);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
	}
}

void	select_exec(t_minishell *shell, char **command)
{
	if (command == NULL)
		return ;
	if (ft_strncmp(command[0], "./minishell", 11) == 0)
	{
		command[0] = shell->executable_path;
		command[1] = NULL;
		execute_subshell(shell, command);
	}
	else
		execute_program(shell, command);
}
