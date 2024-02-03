/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:22:06 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/03 09:01:04 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_command(char **cmd_args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd_args[i] && ft_strncmp(cmd_args[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd_args[i])
	{
		printf("%s", cmd_args[i]);
		if (cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
