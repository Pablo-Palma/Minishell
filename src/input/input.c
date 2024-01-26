/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:53:13 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/27 00:05:45 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_operators(char *input)
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
		if ((input[i] == '>' || input[i] == '<' || input[i] == '|')
			&& !last_quote && !flag)
		{
			counter++;
			flag++;
		}
		else if (input[i] != '>' && input[i] != '<')
			flag = 0;
	}
	return (counter);
}

char	*handle_operators(char *input)
{
	char	*parsed_input;
	int		i;
	int		j;
	int		f;
	int		last_quote;

	parsed_input = calloc(1, ft_strlen(input) + count_operators(input) * 2 + 1);
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
		if ((input[i] == '>' || input[i] == '<' || input[i] == '|') && !f && !last_quote)
		{
			parsed_input[j++] = ' ';
			f++;
		}
		else if (!(input[i] == '>' || input[i] == '<' || input[i] == '|') && f && !last_quote)
		{
			parsed_input[j++] = ' ';
			f = 0;
		}
		parsed_input[j++] = input[i++];
	}
	parsed_input[j] = 0;
	return (parsed_input);
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

int	handle_doc(t_minishell *shell, t_token *tokens)
{
	t_token	*current_token;
	t_token	*delimiter_token;

	current_token = tokens;
	while (current_token != NULL)
	{
		if (current_token->type == AST_HEREDOC)
		{
			if (!current_token->next)
			{
				free_tokens(tokens);
				return (1);
			}
			delimiter_token = current_token->next;
			if (delimiter_token && delimiter_token->type == AST_HEREDOC_DELIM)
			{
				if (g_sigint_recived == SIGINT_HD_RECIVED)
					return (1);
				proccess_heredoc(shell, delimiter_token->value);
			}
		}
		current_token = current_token->next;
	}
	return (0);
}

int	handle_input(t_minishell *shell, char *input)
{
	t_token		*tokens;
	t_ast_node	*ast;
	char		*parsed_input;

	parsed_input = handle_operators(input);
	tokens = lexer(split_input(parsed_input, " "));
	free(parsed_input);
	if (!tokens)
		return (-1);
	handle_envp(shell, tokens);
	if (handle_doc(shell, tokens))
		return (1);
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
