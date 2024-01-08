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

void	execute_subshell(t_minishell *shell)
{
	pid_t	pid;
	int		status;
	char	*args[2];

	pid = fork();
	status = 0;
	args[0] = shell->executable_path;
	args[1] = NULL;
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		if (execve(shell->executable_path, args, shell->og_envp) == -1)
		{
			perror ("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
