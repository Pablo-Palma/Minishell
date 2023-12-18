/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:14:43 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/09 14:17:33 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtin(char **cmd_args, t_minishell *shell)
{
	(void)shell;
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
		export_command(&cmd_args[1], shell);
		return (1);
	}
	else if (strncmp(cmd_args[0], "unset", 5) == 0)
	{
		unset_command(&cmd_args[1], shell);
		return (1);
	}
	else if (strncmp(cmd_args[0], "env", 3) == 0)
	{
		env_command(shell);
		return (1);
	}
	else if (strncmp(cmd_args[0], "exit", 4) == 0)
		exit_command(cmd_args, shell);
	return (0);
}
