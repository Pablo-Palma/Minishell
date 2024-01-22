/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:46:52 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/23 00:22:34 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		update_env_var(&(shell->envp), "OLDPWD", old_path);
		update_env_var(&(shell->envp), "PWD", new_cwd);
	}
	else
	{
		perror("cd failed");
	}
}
