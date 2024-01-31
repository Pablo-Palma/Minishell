/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:27:38 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/27 12:55:15 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(const char *cmd, const char *delim)
{
	int	s_quote;
	int	d_quote;
	int	flag;
	int	count;

	s_quote = 0;
	d_quote = 0;
	count = 0;
	flag = 0;
	while (*cmd)
	{
		if (*cmd == '\'' && !d_quote)
			s_quote = !s_quote;
		if (*cmd == '\"' && !s_quote)
			d_quote = !d_quote;
		if (!s_quote && !d_quote && ft_strchr(delim, *cmd) && flag)
			flag = 0;
		if (!ft_strchr(delim, *cmd) && !flag)
		{
			count++;
			flag++;
		}
		cmd++;
	}
	return (count);
}

static char	*copy_arg(const char **src, const char *delimiters)
{
	const char	*end;
	char		*arg;
	int			s_quote;
	int			d_quote;

	end = *src;
	s_quote = 0;
	d_quote = 0;
	while (*end)
	{
		if (*end == '\'' && !d_quote)
			s_quote = !s_quote;
		if (*end == '\"' && !s_quote)
			d_quote = !d_quote;
		else if (!s_quote && !d_quote && ft_strchr(delimiters, *end))
			break ;
		end++;
	}
	arg = ft_strndup(*src, end - *src + 1);
	arg[end - *src] = '\0';
	if (*end != '\0')
		*src = end + 1;
	else
		*src = end;
	return (arg);
}

char	**split_input(const char *cmd, const char *delimiters)
{
	char	**args;
	int		arg_count;
	int		i;

	i = 0;
	arg_count = count_args(cmd, delimiters);
	args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	while (*cmd)
	{
		while (*cmd && ft_strchr(delimiters, *cmd) != NULL)
			cmd++;
		if (*cmd)
			args[i++] = copy_arg(&cmd, delimiters);
		if (!args[i - 1])
		{
			while (--i > 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
	}
	args[i] = NULL;
	return (args);
}
