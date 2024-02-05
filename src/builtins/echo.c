/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:22:06 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/05 13:54:48 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	newline_checker(char **cmd_args, int *i)
{
	int	j;
	int	nl_checker;
	int	newline;

	nl_checker = 0;
	newline = 1;
	while (cmd_args[*i] && ft_strncmp(cmd_args[*i], "-n", 2) == 0)
	{
		newline = 0;
		j = 1;
		while (cmd_args[*i][j] != '\0')
		{
			if (cmd_args[*i][j] != 'n')
			{
				if (nl_checker)
					return (0);
				return (1);
			}
			j++;
		}
		(*i)++;
		nl_checker = 1;
	}
	return (newline);
}

void	echo_command(char **cmd_args)
{
	int	newline;
	int	i;

	i = 1;
	newline = newline_checker(cmd_args, &i);
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
