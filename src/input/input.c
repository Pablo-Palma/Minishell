/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:53:13 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/15 13:58:02 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strip_quotes(char *quoted_str, char *unquoted_str)
{
	int		i;
	int		j;
	char	last_quote;

	i = 0;
	j = 0;
	last_quote = 0;
	while (quoted_str[i])
	{
		if ((quoted_str[i] == 39 || quoted_str[i] == 34) && last_quote == 0)
			last_quote = quoted_str[i];
		else if (quoted_str[i] == last_quote)
			last_quote = 0;
		else
			unquoted_str[j++] = quoted_str[i];
		i++;
	}
	unquoted_str[j] = 0;
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	handle_input(char *input, t_minishell *shell) //SIN REDIRECCIONES
{
	char	*unquoted_input;

	unquoted_input = malloc(ft_strlen(input) + 1);
	strip_quotes(input, unquoted_input);
	shell->commands = ft_split(unquoted_input, '|');
	shell->number_commands = ft_tablen(shell->commands);
	if (shell->number_commands == 1)
	{
		if (execute_non_pipe_command(shell) == -1)
			ft_printf("ERROR EN EXEC_NON_PIPE_COMMAND");
	}
	else
		if (execute_pipe_command(shell) == -1)
			ft_printf("ERROR EN EXEC_PIPE_COMMAND");
	free(unquoted_input);
	return (1);
}
