/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:11:06 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/16 13:32:17 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char *input, t_minishell *shell)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(input, ' ');
	if(!handle_builtin(cmd_args, shell))
	{	
		if (!cmd_args)
			error("No input detected");
		cmd_path = get_path(cmd_args[0], getenv("PATH"));
		if(!cmd_path)
			error("Command not found");
		if (execve(cmd_path, cmd_args, shell->envp) == -1)
			error("Exec error");
		ft_free_arrays(cmd_args);
		free(cmd_path);
		exit (EXIT_FAILURE);
	}
	else
		exit(0);
	ft_free_arrays(cmd_args);
}
