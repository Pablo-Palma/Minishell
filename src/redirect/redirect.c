/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:24:33 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/15 16:06:55 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	input_redirect(t_minishell *shell, int pos)//Argumentos de entrada según manejemos el input
{
	if (!strchr(shell->commands[pos], '<'))
		shell->input_redirect = NULL;
	else
	{
		shell->input_redirect = open(shell->commands[pos], O_RDONLY, 0777);
		if (shell->input_redirect == -1)
		{
			perror("Error en redirección de entrada");
			return (0);
		}
	}
	/*
	Habría que ajustar el archivo introducido en open, sería buscar el nodo que contenga
	el archivo y usar nodo->data como argumento en open.
	*/
	return (1);
}

static int	output_redirect(t_minishell *shell, int pos);
{
	if (!strchr(shell->commands[pos], '>'))
		shell->output_redirect = NULL;
	else
	{
		shell->output_redirect = open(shell->commands[pos], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (shell->output_redirect == -1)
		{
			perror("Error en redirección de salida");
			return (0);
		}
	}
	/*
	Habría que ajustar el archivo introducido en open, sería buscar el nodo que contenga
	el archivo y usar nodo->data como argumento en open.
	*/
	return (1);
}

int	handle_redirections(t_minishell *shell)
{
	if (!input_redirect(shell, 0) || !output_redirect(shell, shell->number_commands - 1))
		return (0);
	return (1);
}
