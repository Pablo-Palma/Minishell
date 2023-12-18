/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:24:43 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/09 10:29:12 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//1.	Si añadimos una nueva variable shell.envp se sustituye por
//una nueva matriz asignada dinamicamente con malloc, pero hay que checkear 
//que no genere leaks.
//y ver el entorno shell->envp que se recibe en el main como se almacena.
//2.	falta controlar casos especiales como que se exporte una variable vacía
//o que la forma de exportar la variable o cumpla con las convenciones...

void	add_var_envp(t_minishell *shell, const char *new_var)
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

int	process_export(t_minishell *shell, const char *arg)
{
	char		**tokens;
	int			status;
	const char	*delimiters;

	status = 0;
	delimiters = "=";
	tokens = split_cmd(arg, delimiters);
	if (tokens == NULL)
	{
		perror("Errorn en split_cmd");
		return (-1);
	}
	if (tokens[0])
	{
		unset_command(tokens, shell);
		if (tokens[1])
			add_var_envp(shell, arg);
		else
		{
			perror("Invalid export argument");
			status = -1;
		}
	}
	ft_free_arrays(tokens);
	return (status);
}

int	export_command(char **args, t_minishell *shell)
{
	int			i;
	int			ret;
	int			status;

	(void)shell;
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
