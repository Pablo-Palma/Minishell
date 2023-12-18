/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:58:32 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/05 17:02:12 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_cmd_to_dir(const char *dir, const char *cmd)
{
	char	*full_path;
	size_t	len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full_path = malloc(len);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, cmd, len);
	return (full_path);
}

char	*get_path(char *cmd, const char *env_path)
{
	char	**dirs;
	char	*cmd_path;
	int		i;

	i = 0;
	if (cmd[0] == '/' && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	dirs = ft_split(env_path, ':');
	if (!dirs)
		return (NULL);
	cmd_path = NULL;
	while (dirs[i] && cmd_path == NULL)
	{
		cmd_path = join_cmd_to_dir(dirs[i], cmd);
		if (cmd_path && access(cmd_path, X_OK) == 0)
			break ;
		free (cmd_path);
		cmd_path = NULL;
		i++;
	}
	ft_free_arrays(dirs);
	return (cmd_path);
}
