/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:23:34 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/07 11:58:59 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_subshell(t_minishell	*shell)
{
	pid_t pid;
	int	status;
	char	*args[] = {shell->executable_path, NULL};

	pid = fork();
	status = 0;

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
