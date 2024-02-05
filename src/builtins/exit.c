/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 10:49:42 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/05 11:52:08 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Para simular bash exit sale con el comando de salida del último comando
//falta incorporar en la estructura t_minishell una variable que almacene 
//el código de salida del ultimo comando entonces para 1 argumento (exit)
//exit_code = (last_exit_code)

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
			printf("minishell: exit: %s: numeric argument required\n", cmd_args[1]);
		else
			printf("minishell: exit: too many arguments\n");
		exit(2);
	}
	else
	{
		if (ft_strlen(cmd_args[1]) > 3)
			exit(255);
		exit_code = ft_atoi(cmd_args[1]);
		if (exit_code > 255)
			exit(255);
		exit(exit_code);
	}
}
