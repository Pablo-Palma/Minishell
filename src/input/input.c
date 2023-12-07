/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:53:13 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/07 02:59:48 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	handle_input(char *input, t_minishell *shell) //SIN REDIRECCIONES
{
	int	i;

	i = 0;
	shell->commands = ft_split(input, '|');
	shell->number_commands = ft_tablen(shell->commands);
	if (shell->number_commands == 1)
		execute_command(shell->commands[i], shell);
	else
		execute_pipe_command(shell);
	return (1);
}

Se modifica esto en dev?