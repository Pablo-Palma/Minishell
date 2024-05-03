/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 00:22:56 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/30 01:28:18 by jbaeza-c         ###   ########.fr       */
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

int	open_quotes(char *str)
{
	int		i;
	int		envvar;
	char	last_quote;

	i = -1;
	last_quote = 0;
	envvar = 1;
	while (str[++i])
	{
		if (last_quote == 39 && str[i] == '$')
			envvar = 0;
		if ((str[i] == 39 || str[i] == 34) && last_quote == 0)
			last_quote = str[i];
		else if (str[i] == last_quote)
			last_quote = 0;
	}
	if (last_quote)
		return (-1);
	return (envvar);
}
