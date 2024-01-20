/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:46:52 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/07 09:10:39 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_var(t_minishell *shell, const char *key, const char *value)
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
	while (shell->envp[i] != NULL)
	{
		if (ft_strncmp(shell->envp[i], key, key_len) == 0
			&& shell->envp[i][key_len] == '=')
		{
			free(shell->envp[i]);
			shell->envp[i] = new_var;
			return ;
		}
		i++;
	}
	add_var_envp(shell, new_var);
}

void	cd_command(t_minishell *shell, char **cmd_args)
{
	char	new_cwd[PATH_MAX];
	char	old_path[PATH_MAX];
	char	*new_path;

	getcwd(old_path, sizeof(old_path));
	new_path = cmd_args[1];
	if (!new_path)
		new_path = getenv("HOME");
	if (chdir(new_path) == 0)
	{
		getcwd(new_cwd, sizeof(new_cwd));
		update_env_var(shell, "OLDPWD", old_path);
		update_env_var(shell, "PWD", new_cwd);
	}
	else
	{
		perror("cd failed");
	}
}

/*void	cd_command(char **cmd_args)
{
	char	*new_path;
	char	old_path[PATH_MAX];
	char	current_path[PATH_MAX];
	int		chdir_result;

	if (getcwd(old_path, sizeof(old_path)) == NULL)
	{
		perror ("getcwd");
		return ;
	}
	new_path = cmd_args[1];
	if (new_path == NULL)
		new_path = getenv("HOME");
	chdir_result = chdir(new_path);
	if (!chdir_result)
	{
		setenv("OLDPWD", old_path, 1);
		if (getcwd(current_path, sizeof(current_path)) != NULL)
			setenv("PWD", current_path, 1);
		else
			perror("getcwd");
	}
	else
		perror("cd");
}*/
