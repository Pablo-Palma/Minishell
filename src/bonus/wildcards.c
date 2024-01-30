/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:14:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/30 10:12:25 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <minishell.h>

char	**command(char **args, char **files)
{
	char	**command;
	int		i;
	int		j;

	command = malloc(sizeof(char *) * (count_elem(args) + count_elem(files)));
	i = -1;
	j = 0;
	while (args[++i])
	{
		if (ft_strchr(args[i], '*'))
			break ;
		command[i] = ft_strdup(args[i]);
		if (args[i])
			free(args[i]);
	}
	while (files[j])
	{
		command[i++] = ft_strdup(files[j]);
		free(files[j]);
		j++;
	}
	free(files);
	free(args);
	command[i] = NULL;
	return (command);
}

char	*concatenate_path(const char *dir_path, const char *filename)
{
	char	*full_path;
	char	*temp_path;

	if (dir_path[ft_strlen(dir_path) - 1] != '/')
		temp_path = ft_strjoin(dir_path, "/");
	else
		temp_path = ft_strdup(dir_path);
	full_path = ft_strjoin(temp_path, filename);
	free(temp_path);
	return (full_path);
}

char	**expand_wildcards(char **args)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*pattern;
	char			*file_pattern;
	char			*dir_path;
	char			**files;
	int				i;

	pattern = NULL;
	file_pattern = NULL;
	dir_path = NULL;
	i = -1;
	while(args[++i])
	{
		if (ft_strchr(args[i], '*'))
		{
			pattern = args[i];
			break;
		}
	}
	if (!pattern)
		return (NULL);
	if (args[i] == NULL)
		return (NULL);
	split_pattern(pattern, &dir_path, &file_pattern);
	files = malloc(sizeof(char *) * (count_files(file_pattern, dir_path) + 1));
	if (!files)
		return (NULL);
	dir = opendir(dir_path);
	if (dir == NULL)
	{
		perror("opendir");
		return (NULL);
	}
	i = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (match_pattern(entry->d_name, file_pattern))
		{
			files[i] = concatenate_path(dir_path, entry->d_name);
			i++;
		}
	}
	files[i] = NULL;
	closedir(dir);
	if (dir_path)
		free(dir_path);
	if (file_pattern)
		free(file_pattern);
	return (files);
}
