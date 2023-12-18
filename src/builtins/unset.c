/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 07:48:58 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/09 09:30:10 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_var(const char *var_name, int var_len, t_minishell *shell)
{
	int	j;

	j = 0;
	while (shell->envp[j])
	{
		if (ft_strncmp(shell->envp[j], var_name, var_len) == 0
			&& shell->envp[j][var_len] == '=')
			return (j);
		j++;
	}
	return (-1);
}

void	remove_env_var(int index, t_minishell *shell)
{
	int	k;

	k = 0;
	free (shell->envp[index]);
	k = index;
	while (shell->envp[k])
	{
		shell->envp[k] = shell->envp[k + 1];
		k++;
	}
}

int	unset_command(char **args, t_minishell *shell)
{
	int	i;
	int	index;
	int	var_len;

	i = 0;
	if (!args[0])
		return (1);
	while (args[i])
	{
		var_len = ft_strlen(args[i]);
		index = find_env_var(args[i], var_len, shell);
		if (index != -1)
			remove_env_var(index, shell);
		i++;
	}
	return (0);
}
