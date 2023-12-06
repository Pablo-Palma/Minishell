/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:27:38 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/05 16:58:46 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(const char *cmd)
{
	int	in_quote;
	int	count;

	in_quote = 0;
	count = 0;
	while (*cmd)
	{
		if (*cmd == '\'' && (*cmd == cmd[0] || *(cmd - 1) != '\\'))
			in_quote = !in_quote;
		if (*cmd == ' ' && in_quote == 0)
			count++;
		cmd++;
	}
	return (count + 1);
}

static char	*copy_arg(const char **src)
{
	const char	*end;
	char		*arg;
	int			len;

	if (**src == '\'')
	{
		(*src)++;
		end = ft_strchr(*src, '\'');
	}
	else
	{
		end = ft_strchr(*src, ' ');
		if (!end)
			end = *src + ft_strlen(*src);
	}
	len = end - *src;
	arg = (char *)malloc(sizeof(char) * (len + 1));
	if (!arg)
		return (NULL);
	ft_strlcpy(arg, *src, len + 1);
	*src = end + (*end == '\'' || *end == ' ');
	return (arg);
}

char	**split_cmd(const char *cmd)
{
	char	**args;
	int		arg_count;
	int		i;

	i = 0;
	arg_count = count_args(cmd);
	args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	while (*cmd)
	{
		while (*cmd == ' ')
			cmd++;
		while (*cmd)
			args[i++] = copy_arg(&cmd);
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
