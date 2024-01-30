/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:13:21 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/30 12:26:00 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_quotes(char *input)
{
	int		i;
	int		j;
	char	*p_input;
	char	last_quote;

	i = 0;
	j = 0;
	last_quote = 0;
	p_input = malloc(ft_strlen(input) + 1);
	if (!p_input)
		return (NULL);
	while (input[i])
	{
		if ((input[i] == 39 || input[i] == 34) && last_quote == 0)
			last_quote = input[i];
		else if (input[i] == last_quote)
			last_quote = 0;
		else
			p_input[j++] = input[i];
		i++;
	}
	p_input[j] = 0;
	free(input);
	return (p_input);
}

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
