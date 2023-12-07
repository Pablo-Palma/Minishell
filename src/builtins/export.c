/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:24:43 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/07 16:49:21 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//1.	Si añadimos una nueva variable shell.envp se sustituye por
//una nueva matriz asignada dinamicamente con malloc, pero hay que checkear 
//que no genere leaks.
//y ver el entorno shell->envp que se recibe en el main como se almacena.
//2.	falta controlar casos especiales como que se exporte una variable vacía
//o que la forma de exportar la variable o cumpla con las convenciones...

void	add_var_envp(t_minishell *shell, char *new_var)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (shell->envp[i] != NULL)
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (shell->envp[i] != NULL)
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(new_var);
	new_envp[i + 1] = NULL;
	shell->envp = new_envp;
}

int	export_command(char **args, t_minishell *shell)
{
	char		**tokens;
	const char	*delimiters;
	int			i;
	int			j;
	int			status;

	(void)shell;
	i = 0;
	j = 0;
	delimiters = "=";
	status = 0;
	if (args[0] == NULL)
	{
		while (shell->envp[i] != NULL)
		{
			printf("%s\n", shell->envp[i]);
			i++;
		}
	}
	else
	{
		while (args[i])
		{
			tokens = split_cmd(args[i], delimiters);
			if (tokens == NULL)
			{
				perror("Error en split_cmd");
				return (-1);
			}
			if (tokens[0] && tokens[1])
			{
				if (setenv(tokens[0], tokens[1], 1) != 0)
				{
					perror("setenv");
					status = -1;
				}
				else
					add_var_envp(shell, args[i]);
			}
			else if (tokens[0] && !tokens[1])
				printf("%s", tokens[0]);
			while (tokens[j] != NULL)
				free(tokens[j++]);
			free(tokens);
			i++;
		}
	}
	return (status);
}
