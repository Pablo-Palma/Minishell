/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:27:38 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/07 12:58:23 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//falta ver que hacer con comillas sin cerrar

static int	count_args(const char *cmd, const char *delimiters)
{
	int	in_single_quote;
	int	in_double_quote;
	int	count;

	in_single_quote = 0;
	in_double_quote = 0;
	count = 0;
	while (*cmd)
	{
		if (*cmd == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*cmd == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote &&ft_strchr(delimiters, *cmd) != NULL)
			count++;
		cmd++;
	}
	return (count + 1);
}

static char	*copy_arg(const char **src, const char *delimiters)
{
	const char	*end;
	char		*arg;
	int			len;
	int			in_single_quote;
	int			in_double_quote;

	end = *src;
	in_single_quote = 0;
	in_double_quote = 0;
	while (*end)
	{
		if (*end == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		if (*end == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote && ft_strchr(delimiters, *end)  != NULL)
			break ;
		end++;
	}
	len = end - *src;
	arg = (char *)malloc(sizeof(char) * (len + 1));
	if (!arg)
		return (NULL);
	ft_strlcpy(arg, *src, len + 1);
	arg[len] = '\0';
	if (*end != '\0')
		*src = end + 1;
	else
		*src = end;
	return (arg);
}

char	**split_cmd(const char *cmd, const char *delimiters)
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
		while (ft_strchr(delimiters, *cmd) != NULL)
			cmd++;
		while (*cmd)
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
