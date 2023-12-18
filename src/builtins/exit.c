/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 10:49:42 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/09 11:29:17 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Para simular bash exit sale con el comando de salida del último comando
//falta incorporar en la estructura t_minishell una variable que almacene 
//el código de salida del ultimo comando entonces para 1 argumento (exit)
//exit_code = (last_exit_code)

int	exit_command(char **cmd_args, t_minishell *shell)
{
	int	exit_code;

	(void)shell;
	exit_code = 0;
	if (cmd_args[1] == NULL)
	{
		printf("exit\n");
		exit(exit_code);
	}
	else if (ft_isnumeric(cmd_args[1]) && cmd_args[2] == NULL)
	{
		exit_code = ft_atoi(cmd_args[1]);
		exit(exit_code);
	}
	else
	{
		printf("minishell: exit %s: numeric argument required\n", cmd_args[1]);
		return (1);
	}
}
