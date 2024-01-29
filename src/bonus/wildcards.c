/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:14:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/29 19:29:42 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <minishell.h>

int    match_pattern(const char *filename, const char *pattern)
{
    const char    *pat_ptr = pattern;
    const char    *file_ptr = filename;
    const char    *last_match = NULL;

    if (filename[0] == '.')
        return (0);
    while (*pat_ptr && *file_ptr)
    {
        if (*pat_ptr == '*') // MANEJAMOS ASTERISCO AL INICIO
        {
            while (*pat_ptr == '*')
              pat_ptr++;
            if (!pat_ptr) //solo un asterisco
                return 1;
            while (*file_ptr && *file_ptr != *pat_ptr) //recorrer filename hasta encontrar coicidencia
                file_ptr++;
        }
        else //MANEJAMOS ASTERISCO AL FINAL
        {
            if (*file_ptr == *pat_ptr) //Mientras coicidan recorremos
            {
                last_match = pat_ptr;
                file_ptr++;
                pat_ptr++;
            }
            else
                return (0);
        }
            if (*file_ptr && !*pat_ptr)
              pat_ptr = last_match;
    }
	while (*pat_ptr == '*')
		pat_ptr++;
    if (!*file_ptr && !*pat_ptr)
        return (1);
    return (0);
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
