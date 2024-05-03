/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:49:15 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/02/01 18:55:44 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*concatenate_path(const char *dir_path, const char *filename)
{
	char	*full_path;
	char	*temp_path;

	if (ft_strncmp(dir_path, ".", 2) == 0)
		return (ft_strdup(filename));
	if (dir_path[ft_strlen(dir_path) - 1] != '/')
		temp_path = ft_strjoin(dir_path, "/");
	else
		temp_path = ft_strdup(dir_path);
	full_path = ft_strjoin(temp_path, filename);
	free(temp_path);
	return (full_path);
}

void	split_pattern(const char *pat, char **dir_path, char **file_pat)
{
	char	*last_slash;

	last_slash = ft_strrchr(pat, '/');
	if (last_slash != NULL)
	{
		*dir_path = ft_strndup(pat, last_slash - pat + 1);
		*file_pat = ft_strdup(last_slash + 1);
	}
	else
	{
		*dir_path = ft_strdup(".");
		*file_pat = ft_strdup(pat);
	}
}

static int	aux_match(const char **pat, const char **file, const char **last)
{
	if (*(*pat) == '*')
	{
		while (*(*pat) == '*')
			(*pat)++;
		if (!(*pat))
			return (1);
		while (*(*file) && *(*file) != *(*pat))
			(*file)++;
	}
	else
	{
		if (*(*file) != *(*pat))
			return (0);
		*last = *pat;
		(*file)++;
		(*pat)++;
	}
	if (*(*file) && !*(*pat))
		*pat = *last;
	return (2);
}

int	match_pattern(const char *filename, const char *pattern)
{
	const char	*pat_ptr;
	const char	*file_ptr;
	const char	*last_match;
	int			aux_return;

	pat_ptr = pattern;
	file_ptr = filename;
	last_match = NULL;
	if (filename[0] == '.')
		return (0);
	while (*pat_ptr && *file_ptr)
	{
		aux_return = aux_match(&pat_ptr, &file_ptr, &last_match);
		if (aux_return == 1 || !aux_return)
			return (aux_return);
	}
	while (*pat_ptr == '*')
		pat_ptr++;
	if (!*file_ptr && !*pat_ptr)
		return (1);
	return (0);
}

int	cnt_files(char *pattern, char *dir_path)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(dir_path);
	if (dir == NULL)
	{
		perror("opendir");
		return (0);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (match_pattern(entry->d_name, pattern))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}
