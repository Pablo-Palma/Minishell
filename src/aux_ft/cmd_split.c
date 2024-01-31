/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:13:21 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/30 00:23:17 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_cmd(const char *s, char *delim)
{
	char	**tab;
	int		i;

	i = -1;
	tab = split_input(s, delim);
	if (!tab)
		return (NULL);
	while (tab[++i])
		tab[i] = strip_quotes(tab[i]);
	return (tab);
}
