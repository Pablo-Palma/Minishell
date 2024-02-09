/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:53:13 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/02/06 16:49:58 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_op(char *input, char *operators)
{
	int	flag;
	int	counter;
	int	i;
	int	last_quote;

	flag = 0;
	counter = 0;
	last_quote = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == last_quote)
			last_quote = 0;
		if (!last_quote && (input[i] == 34 || input[i] == 39))
			last_quote = input[i];
		if (ft_strchr(operators, input[i])
			&& !last_quote && !flag)
		{
			counter++;
			flag++;
		}
		else if (!ft_strchr(operators, input[i]))
			flag = 0;
	}
	return (counter);
}

void	handle_operators(char *input, char *p_input, char *operators)
{
	int		i;
	int		j;
	int		f;
	int		last_quote;

	i = 0;
	j = 0;
	f = 0;
	last_quote = 0;
	while (input[i])
	{
		if (input[i] == last_quote)
			last_quote = 0;
		if (!last_quote && (input[i] == 34 || input[i] == 39))
			last_quote = input[i];
		if ((ft_strchr(operators, input[i]) && !f && !last_quote)
			|| (!ft_strchr(operators, input[i]) && f))
		{
			p_input[j++] = ' ';
			f = 1;
			if (!ft_strchr(operators, input[i]))
				f = 0;
		}
		p_input[j++] = input[i++];
	}
}

int	handle_input(t_minishell *shell, char *input)
{
	t_token		*tokens;
	t_ast_node	*ast;
	char		*p_input;

	p_input = ft_calloc(1, ft_strlen(input) + count_op(input, "<>|&") * 2 + 1);
	handle_operators(input, p_input, "<>|&");
	tokens = lexer(split_input(p_input, " "));
	free(p_input);
	handle_envp(shell, tokens);
	if (!tokens)
		return (-1);
	ast = build_ast(tokens);
	if (!ast)
	{
		free_tokens(tokens);
		return (-1);
	}
	execute_ast_command(shell, ast);
	free_ast(ast);
	free_tokens(tokens);
	reset_minishell(shell);
	return (1);
}
