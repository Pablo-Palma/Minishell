/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 10:49:42 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/07 08:02:28 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_command(t_minishell *shell, char **cmd_args)
{
	int	exit_code;

	exit_code = shell->last_exit_status;
	free_shell(shell);
	printf("exit\n");
	if (cmd_args[1] == NULL)
		exit(exit_code);
	else if (!ft_isnumeric(cmd_args[1]) || cmd_args[2])
	{
		if (!cmd_args[2])
			printf("minishell: exit: %s: numeric argument required\n",
				cmd_args[1]);
		else
			printf("minishell: exit: too many arguments\n");
		exit(255);
	}
	else
	{
		if (ft_strlen(cmd_args[1]) > 18)
			exit(255);
		else if (cmd_args[1])
			exit_code = ft_atoi(cmd_args[1]);
		exit(exit_code % 256);
	}
}
