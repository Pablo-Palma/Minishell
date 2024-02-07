/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:24:43 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/07 16:52:42 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_varname(const char *name)
{
	int	equal;

	equal = 0;
	if (!name || !*name || (!ft_isalpha(*name) && *name != '_'))
		return (0);
	while (*name)
	{
		if (*name == '=')
			equal = 1;
		if (!ft_isalnum(*name) && *name != '=' && *name != '_')
			return (0);
		name++;
	}
	return (equal);
}

int	process_export(t_minishell *shell, const char *arg)
{
	char		**tokens;
	int			status;

	status = 0;
	if (!is_valid_varname(arg))
		return (printf("msh: %s Invalid export argument\n", arg), -1);
	tokens = ft_split(arg, '=');
	if (tokens == NULL)
	{
		perror("Error en split_cmd");
		return (-1);
	}
	if (tokens[0])
	{
		unset_command(shell, tokens);
		if (arg)
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
