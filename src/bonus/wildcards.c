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
	j = -1;
	while (args[++i])
	{
		if (ft_strchr(args[i], '*'))
			break ;
		command[i] = ft_strdup(args[i]);
	}
	while (files[++j])
		command[i++] = ft_strdup(files[j]);
	ft_free_arrays(files);
	ft_free_arrays(args);
	command[i] = NULL;
	return (command);
}

static char	*find_wildcard(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		if (ft_strchr(args[i], '*'))
			return (ft_strdup(args[i]));
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
	if (wc->pat)
		free(wc->pat);
	if (!n)
	{
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
