/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:53:13 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/24 10:09:49 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_operators(char *input)
{
	int	flag;
	int	counter;
	int	i;

	flag = 0;
	counter = 0;
	i = -1;
	while (input[++i])
	{
		if ((input[i] == '>' || input[i] == '<' || input[i] == '|') && !flag)
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

	parsed_input = malloc(ft_strlen(input) + count_operators(input) * 2 + 1);
	i = 0;
	j = 0;
	f = 0;
	while (input[i])
	{
		if ((input[i] == '>' || input[i] == '<' || input[i] == '|') && !f)
		{
			parsed_input[j++] = ' ';
			f++;
		}
		else if (!(input[i] == '>' || input[i] == '<' || input[i] == '|') && f)
		{
			parsed_input[j++] = ' ';
			f = 0;
		}
		parsed_input[j++] = input[i++];
	}
	parsed_input[j] = 0;
	return (parsed_input);
}

int	strip_quotes(char *quoted_str, char *unquoted_str)
{
	int		i;
	int		j;
	int		envvar;
	char	last_quote;

	i = 0;
	j = 0;
	last_quote = 0;
	envvar = 1;
	while (quoted_str[i])
	{
		if (last_quote == 39 && quoted_str[i] == '$')
			envvar = 0;
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
				return (1);
			delimiter_token = current_token->next;
			if (delimiter_token && delimiter_token->type == AST_HEREDOC_DELIM)
			{
				if (g_sigint_recived == SIGINT_HD_RECIVED)
					return (1);
				proccess_heredoc(shell, delimiter_token->value);
				current_token = current_token->next;
			}
		}
		else
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
	tokens = lexer(split_cmd(parsed_input, " "));
	free(parsed_input);
	handle_envp(shell, tokens);
	if (!tokens)
		return (-1);
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
