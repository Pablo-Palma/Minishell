/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:14:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/30 11:13:49 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*find_wildcard(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		if (ft_strchr(args[i], '*'))
			return (args[i]);
	return (NULL);
}

static void	init_wildcard(t_wildcard *wc)
{
	wc->dir = NULL;
	wc->entry = NULL;
	wc->pat = NULL;
	wc->f_pat = NULL;
	wc->dir_path = NULL;
	wc->files = NULL;
}

static char	**wildcard_exit(t_wildcard *wc, int n, char *error)
{
	if (error)
		perror(error);
	if (wc->dir)
		closedir(wc->dir);
	if (wc->f_pat)
		free(wc->f_pat);
	if (wc->dir_path)
		free(wc->dir_path);
	if (!n)
	{
		if (wc->pat)
			free(wc->pat);
		if (wc->files)
			free(wc->files);
		return (NULL);
	}
	return (wc->files);
}

char	**expand_wildcards(char **args)
{
	t_wildcard	wc;
	int			i;

	init_wildcard(&wc);
	wc.pat = find_wildcard(args);
	if (!wc.pat)
		return (wildcard_exit(&wc, 0, NULL));
	split_pattern(wc.pat, &(wc.dir_path), &(wc.f_pat));
	wc.files = malloc(sizeof(char *) * (cnt_files(wc.f_pat, wc.dir_path) + 1));
	if (!wc.files)
		return (wildcard_exit(&wc, 0, NULL));
	wc.dir = opendir(wc.dir_path);
	if (wc.dir == NULL)
		return (wildcard_exit(&wc, 0, "Opendir Error"));
	i = 0;
	wc.entry = readdir(wc.dir);
	while (wc.entry != NULL)
	{
		if (match_pattern(wc.entry->d_name, wc.f_pat))
			wc.files[i++] = concatenate_path(wc.dir_path, wc.entry->d_name);	
		wc.entry = readdir(wc.dir);
	}	
	wc.files[i] = NULL;
	return (wildcard_exit(&wc, 1, NULL));
}
