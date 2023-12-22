/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:53:13 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/21 11:37:55 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strip_quotes(char *quoted_str, char *unquoted_str)
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
	if (last_quote)
		return (0);
	return (1);
}

int	handle_input(t_minishell *shell, char *input) 
{
	char	*unquoted_input;

	unquoted_input = malloc(ft_strlen(input) + 1);
	if (strip_quotes(input, unquoted_input))
	{
		t_token	*tokens = lexer(unquoted_input);
		if (!tokens)
		{
			ft_printf("ERROR generating tokens");
			return (-1);
		}
		t_ast_node *ast = build_ast(tokens);
		if (!ast)
		{
			ft_printf("ERROR building AST");
			free_tokens(tokens);
			return (-1);
		}
		execute_ast_command(shell, ast);
		free_ast(ast);
		free_tokens(tokens);
	}
	else
		printf("Incorrect input\n");
	free(unquoted_input);
	return(1);
}
