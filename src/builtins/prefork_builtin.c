/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefork_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:31:17 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/16 12:37:58 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prefork_builtin(t_minishell *shell)
{
	char	**cmd_args;

	cmd_args = ft_split(shell->commands[0], ' ');
	if (strncmp(cmd_args[0], "cd", 2) == 0)
	{
		cd_command(cmd_args);
		return (1);
	}
	else if (strncmp(cmd_args[0], "export", 6) == 0)
	{
		export_command(&cmd_args[1], shell);
		return (1);
	}
	else if (strncmp(cmd_args[0], "unset", 5) == 0)
	{
		unset_command(&cmd_args[1], shell);
		return (1);
	}
	else if (strncmp(cmd_args[0], "exit", 4) == 0)
		exit_command(cmd_args, shell);
	return (0);
}