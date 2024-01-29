/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:14:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/29 15:27:45 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <minishell.h>

//int	match_pattern

int	count_elements(char **array)
{
	int	count = 0;

	while(array && array[count])
			count++;
	return (count);
}

int	count_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count = 0;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return (0);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
			count++;
	}
	closedir(dir);
	return (count);
}

char	**command(char **args, char **files)
{
	char	**command = NULL;
	int		i = 0;
	int		j = 0;
	int		count = count_elements(args) + count_elements(files);

	command = malloc(sizeof(char *) * (count));
	while (args[i] && ft_strncmp(args[i], "*", 2) != 0)
	{
		command[i] = ft_strdup(args[i]);
		free(args[i]);
		i++;
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

char	**expand_wildcards(char **args)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				i = 0;
	int				count = 0;

	while(args[i])
	{
		if (ft_strncmp(args[i], "*", 1) == 0)
			break;
		i++;
	}
	if (args[i] == NULL)
		return (NULL);
	count = count_files();
	files = malloc(sizeof(char *) * (count + 1));
	if (!files)
		return (NULL);
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return (NULL);
	}
	i = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			files[i] = ft_strdup(entry->d_name);
			i++;
		}
	}
	files[i] = NULL;
	closedir(dir);
	return (files);
}
