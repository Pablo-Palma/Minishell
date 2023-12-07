/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:14:43 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/07 14:03:40 by pabpalma         ###   ########.fr       */
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
	return (0);
}
