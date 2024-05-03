/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:27:38 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/07 13:12:37 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_delim(int input, int *last_quote, int *brackets)
{
	if (!*last_quote && input == '(')
		*brackets = *brackets + 1;
	else if (!*last_quote && input == ')')
		*brackets = *brackets - 1;
	else if (input == *last_quote && !*brackets)
		*last_quote = 0;
	else if (!*last_quote && (input == 34 || input == 39) && !*brackets)
		*last_quote = input;
	return (*brackets);
}

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
		if (set_delim(*cmd, &last_quote, &brackets) < 0)
			return (-1);
		if (!brackets && !last_quote && ft_strchr(delim, *cmd) && flag)
			flag = 0;
		if (!ft_strchr(delim, *cmd) && !flag)
		{
			count++;
			flag++;
		}
		cmd++;
	}
	if (brackets)
		return (-1);
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
		set_delim(*end, &last_quote, &brackets);
		if (!brackets && !last_quote && ft_strchr(delimiters, *end))
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

char	**split_input(const char *cmd, const char *delimiters)
{
	char	**args;
	int		arg_count;
	int		i;

	i = 0;
	arg_count = count_args(cmd, delimiters);
	if (arg_count == -1)
		return (printf("msh: syntax error: open brackets\n"), NULL);
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
			free_tab(args, i);
			return (NULL);
		}
	}
	args[i] = NULL;
	return (args);
}
