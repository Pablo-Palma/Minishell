/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:24:43 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/20 14:07:12 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//1.	Si añadimos una nueva variable shell.envp se sustituye por
//una nueva matriz asignada dinamicamente con malloc, pero hay que checkear 
//que no genere leaks.
//y ver el entorno shell->envp que se recibe en el main como se almacena.
//2.	falta controlar casos especiales como que se exporte una variable vacía
//o que la forma de exportar la variable o cumpla con las convenciones...

int	process_export(t_minishell *shell, const char *arg)
{
	char		**tokens;
	int			status;

	status = 0;
	tokens = ft_split(arg, '=');
	if (tokens == NULL)
	{
		perror("Errorn en split_cmd");
		return (-1);
	}
	if (tokens[0])
	{
		unset_command(shell, tokens);
		if (tokens[1])
			add_var_envp(&(shell->envp), arg);
		else
		{
			perror("Invalid export argument");
			status = -1;
		}
	}
	ft_free_arrays(tokens);
	return (status);
}

int	export_command(t_minishell *shell, char **args)
{
	int			i;
	int			ret;
	int			status;

	ret = 0;
	i = 0;
	status = 0;
	if (args[0] == NULL)
		env_command(shell);
	else
	{
		while (args[i])
		{
			ret = process_export(shell, args[i]);
			if (ret != 0)
				status = ret;
			i++;
		}
	}
	return (status);
}
