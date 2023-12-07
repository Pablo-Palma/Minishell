/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:22:06 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/07 08:29:47 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_command(char **cmd_args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd_args[1] && strncmp(cmd_args[1], "-n", 2) == 0)
	{
		newline = 0;
		i = 2;
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
