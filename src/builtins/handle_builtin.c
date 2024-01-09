/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:14:43 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/18 21:01:51 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtin(t_minishell *shell, char **cmd_args)
{
	if (strncmp(cmd_args[0], "echo", 4) == 0)
	{
		echo_command(cmd_args);
		return (1);
	}
	else if (strncmp(cmd_args[0], "cd", 2) == 0)
	{
		cd_command(cmd_args);
		return (1);
	}
	else if (strncmp(cmd_args[0], "pwd", 3) == 0)
	{
		pwd_command();
		return (1);
	}
	else if (strncmp(cmd_args[0], "export", 6) == 0)
	{
		export_command(shell, &cmd_args[1]);
		return (1);
	}
	else if (strncmp(cmd_args[0], "unset", 5) == 0)
	{
		unset_command(shell, &cmd_args[1]);
		return (1);
	}
	else if (strncmp(cmd_args[0], "env", 3) == 0)
	{
		env_command(shell);
		return (1);
	}
	else if (strncmp(cmd_args[0], "exit", 4) == 0)
		exit_command(shell, cmd_args);
	return (0);
}
