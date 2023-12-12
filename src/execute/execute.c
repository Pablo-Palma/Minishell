/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:11:06 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/10 18:51:03 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char *input, t_minishell *shell)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = split_cmd(input, " ");
	if(!handle_builtin(cmd_args, shell))
	{	
		if (!cmd_args)
			perror("Command not found");
		cmd_path = get_path(cmd_args[0], getenv("PATH"));
		if(!cmd_path)
			exit(EXIT_FAILURE);
		execve(cmd_path, cmd_args, shell->envp);
		ft_free_arrays(cmd_args);
		free(cmd_path);
		exit (EXIT_FAILURE);
	}
	else
		exit(0);
	ft_free_arrays(cmd_args);
}
