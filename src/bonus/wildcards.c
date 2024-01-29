/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:14:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/29 16:16:54 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <minishell.h>

int	match_pattern(const char *filename, const char *pattern)
{
	int	pat_len = ft_strlen(pattern);
	int	filename_len = ft_strlen(filename);
	char	*star = ft_strchr(pattern, '*');
	int	prefix_len = star - pattern;
	int	suffix_len = pat_len - prefix_len - 1;

	if (filename[0] == '.')
		return (0);
	if (ft_strncmp(pattern, "*", 2) == 0)
		return(1);
	if (pattern[pat_len - 1] == '*')
        return ft_strncmp(filename, pattern, pat_len - 1) == 0;
	if (pattern[0] == '*')
		return ft_strncmp(filename + filename_len - (pat_len - 1), pattern + 1, pat_len - 1) == 0;
	else
	{
		if (prefix_len > filename_len || suffix_len > filename_len)
			return (0);
		return ft_strncmp(filename, pattern, prefix_len) == 0 &&
				ft_strncmp(filename + filename_len - suffix_len + 1, star + 1,suffix_len) == 0;
	}
	//return ft_strncmp(filename, pattern, pat_len) == 0;
}

int	count_elements(char **array)
{
	int	count = 0;

	while(array && array[count])
			count++;
	return (count);
}

int	count_files(char *pattern)
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
		if (match_pattern(entry->d_name, pattern))
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
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
			break ;
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
	char			*pattern = NULL;
	char			**files;
	int				i = 0;
	int				count = 0;

	while(args[i])
	{
		if (ft_strchr(args[i], '*'))
		{
			pattern = args[i];
			break;
		}
		i++;
	}
	if (!pattern)
		return (NULL);
	if (args[i] == NULL)
		return (NULL);
	count = count_files(pattern);
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
		if (match_pattern(entry->d_name, pattern))
		{
			files[i] = ft_strdup(entry->d_name);
			i++;
		}
	}
	files[i] = NULL;
	closedir(dir);
	return (files);
}
