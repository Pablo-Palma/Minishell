/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:46:20 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/15 20:46:36 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getenv(char **envp, const char *name)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(name);
	if (name == NULL || envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	free_env(char ***env)
{
	int	i;

	i = 0;
	if (env && *env)
	{
		while ((*env)[i] != NULL)
		{
			free((*env)[i]);
			(*env)[i] = NULL;
			i++;
		}
		free(*env);
		*env = NULL;
	}
}

void	add_var_envp(char ***envp, const char *new_var)
{
	int		i;
	char	**new_envp;

	i = 0;
	while ((*envp)[i] != NULL)
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return ;
	i = 0;
	while ((*envp)[i] != NULL)
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new_envp[i] = ft_strdup(new_var);
	new_envp[i + 1] = NULL;
	*envp = new_envp;
}

void	update_env_var(char ***envp, const char *key, const char *value)
{
	char	*new_var;
	char	*temp;
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	temp = ft_strjoin(key, "=");
	new_var = ft_strjoin(temp, value);
	free(temp);
	while ((*envp)[i] != NULL)
	{
		if (ft_strncmp((*envp)[i], key, key_len) == 0
			&& (*envp)[i][key_len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_var;
			return ;
		}
		i++;
	}
	add_var_envp(envp, new_var);
}

void	increment_shlvl(t_minishell *shell)
{
	char	*value_str;
	int		value;
	char	*new_str;

	value_str = getenv("SHLVL");
	if (value_str != NULL)
	{
		value = ft_atoi(value_str);
		value++;
	}
	else
		value = 1;
	new_str = ft_itoa(value);
	update_env_var(&(shell->og_envp), "SHLVL", new_str);
	free(new_str);
}
