/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:14:43 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/10 13:39:18 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_builtin(t_minishell *shell, char **cmd_args)
{
	if (strncmp(cmd_args[0], "cd", 3) == 0)
	{
		cd_command(shell, cmd_args);
		return (1);
	}
	else if (strncmp(cmd_args[0], "export", 7) == 0)
	{
		export_command(shell, &cmd_args[1]);
		return (1);
	}
	else if (strncmp(cmd_args[0], "unset", 6) == 0)
	{
		unset_command(shell, &cmd_args[1]);
		return (1);
	}
	else if (strncmp(cmd_args[0], "exit", 5) == 0)
		exit_command(shell, cmd_args);
	return (0);
}

int	handle_builtin(t_minishell *shell, char **cmd_args)
{
	char	*path;

	path = "/bin/echo";
	if (strncmp(cmd_args[0], "echo", 5) == 0)
	{
		if (cmd_args[1] && ft_strncmp(cmd_args[1], "$$", 3) == 0)
			execute_single_cmd_process(shell, cmd_args, path);
		else if (cmd_args[1] && ft_strncmp(cmd_args[1], "$?", 3) == 0)
			printf("%d\n", shell->last_exit_status);
		else
			echo_command(cmd_args);
		return (1);
	}
	else if (strncmp(cmd_args[0], "pwd", 4) == 0)
	{
		pwd_command();
		return (1);
	}
	else if (strncmp(cmd_args[0], "env", 4) == 0)
	{
		env_command(shell);
		return (1);
	}
	return (0);
}
