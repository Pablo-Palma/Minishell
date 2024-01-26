/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:13:21 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/26 11:23:28 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(const char *str, char *delim)
{
	int			flag;
	int			count;
	const char	*aux;

	aux = str;
	flag = 0;
	count = 0;
	while (*aux)
	{
		if (ft_strchr(delim, *aux) && flag)
			flag = 0;
		if (!ft_strchr(delim, *aux) && !flag)
		{
			count++;
			flag++;
		}
		aux++;
	}
	return (count);
}

static int	custom_len(const char *s, char *delim)
{
	int			len;
	int			flag;

	len = 0;
	flag = 0;
	while (s[len])
	{
		if (ft_strchr(delim, s[len]) && flag)
			flag = 2;
		if (!ft_strchr(delim, s[len]) && flag == 2)
			return (len - 1);
		if (!ft_strchr(delim, s[len]))
			flag = 1;
		len++;
	}
	return (len);
}

static void	free_tab(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**split_cmd(const char *s, char *delim)
{
	char	**tab;
	int		i;
	int		j;
	int		len;

	j = count_words(s, delim);
	i = 0;
	tab = malloc(sizeof(char *) * (j + 1));
	if (!tab)
		return (NULL);
	while (*s && j > 0)
	{
		if (ft_strchr(delim, *s))
			s++;
		len = custom_len(s, delim);
		tab[i] = ft_strndup(s, len + 1);
		if (!tab[i])
			return (free_tab(tab, i + 1), NULL);
		s = s + len;
		printf("Value: %s, Len: %d\n", tab[i], len);
		i++;
		j--;
	}
	tab[i] = NULL;
	return (tab);
}
