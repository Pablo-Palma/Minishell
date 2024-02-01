/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:27:38 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/01 13:38:54 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(const char *cmd, const char *delim)
{
	int	last_quote;
	int	flag;
	int	count;
	int	brackets;

	last_quote = 0;
	count = 0;
	flag = 0;
	brackets = 0;
	while (*cmd)
	{
		if (!last_quote && *cmd == '(')
			brackets++;
		else if (!last_quote && *cmd == ')')
			brackets--;
		else if (*cmd == last_quote && !brackets)
			last_quote = 0;
		else if (!last_quote && (*cmd == 34 || *cmd == 39) && !brackets)
			last_quote = *cmd;
		if (!brackets && !last_quote && ft_strchr(delim, *cmd) && flag)
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
	int			last_quote;
	int			brackets;

	end = *src;
	last_quote = 0;
	brackets = 0;
	while (*end)
	{
		if (!last_quote && *end == '(')
			brackets++;
		else if (!last_quote && *end == ')')
			brackets--;
		if (*end == last_quote && !brackets)
			last_quote = 0;
		else if (!last_quote && (*end == 34 || *end == 39) && !brackets)
			last_quote = *end;
		else if (!brackets && !last_quote && ft_strchr(delimiters, *end))
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
