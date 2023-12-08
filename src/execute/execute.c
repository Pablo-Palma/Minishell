/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:11:06 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/08 21:15:44 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char *input, t_minishell *shell)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = split_cmd(input, " ");
	if (!cmd_args)
		perror("Command not found");
	cmd_path = get_path(cmd_args[0], getenv("PATH"));
	if(!cmd_path)
		exit(EXIT_FAILURE);
	execve(cmd_path, cmd_args, shell->envp);
	ft_free_arrays(cmd_args);
	free(cmd_path);
	exit (EXIT_FAILURE);
	ft_free_arrays(cmd_args);
}
