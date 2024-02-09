/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:37:07 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/07 14:47:26 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_heredoc(char **input, int *i, t_token **tokens)
{
	if (add_token_back(tokens, create_token(AST_HEREDOC, input[*i])) == -1)
		return (-1);
	(*i)++;
	while (input[*i] != NULL && ft_strlen(input[*i]) == 0)
		(*i)++;
	if (input[*i] != NULL)
	{
		if (add_token_back(tokens, create_token(AST_HEREDOC_DELIM,
					input[*i])) == -1)
			return (-1);
		(*i)++;
	}
	(*i)--;
	return (1);
}

t_token	*build_command_token(char **input, int *i)
{
	char		*command;
	char		*temp;
	t_token		*new_token;

	command = ft_strdup(input[*i]);
	(*i)++;
	while (input[*i] != NULL && token_type(input[*i]) == AST_COMMAND)
	{
		temp = command;
		command = ft_strjoin(command, " ");
		if (!command)
			return (NULL);
		free(temp);
		temp = command;
		command = ft_strjoin(command, input[*i]);
		if (!command)
			return (NULL);
		free(temp);
		(*i)++;
	}
	new_token = create_token(AST_COMMAND, command);
	free (command);
	(*i)--;
	return (new_token);
}

int	build_token(t_token **tokens, char **input, int *i, int *is_file)
{
	t_type	type;
	int		status;

	type = token_type(input[*i]);
	if (*is_file)
	{
		if (ft_strchr("|<>&()", *input[*i]) != NULL)
			return (-1);
		status = add_token_back(tokens, create_token(AST_FILE, input[*i]));
		*is_file = 0;
	}
	else if (type == AST_COMMAND)
		status = add_token_back(tokens, build_command_token(input, i));
	else if (type == AST_HEREDOC)
		status = build_heredoc(input, i, tokens);
	else if (type == AST_SUBSHELL_EX)
		status = add_token_back(tokens, create_token(type, input[*i]));
	else
	{
		if (type == AST_REDIRECT_IN || type == AST_REDIRECT_OUT)
			*is_file = 1;
		status = add_token_back(tokens, create_token(type, input[*i]));
	}
	return (status);
}

void	build_collapsed_token(t_token **root, t_token *token)
{
	char	*value;
	char	*temp;

	while (token)
	{
		if (token->type == AST_COMMAND)
		{
			value = ft_strdup(token->value);
			while (token->next && token->next->type == AST_COMMAND)
			{
				temp = ft_strjoin(value, " ");
				free(value);
				value = ft_strjoin(temp, token->next->value);
				free(temp);
				token = token->next;
			}
			add_token_back(root, create_token(AST_COMMAND, value));
			free(value);
		}
		else
			add_token_back(root, create_token(token->type, token->value));
		token = token->next;
	}
}

t_token	*lexer(char **input)
{
	t_token	*tokens;
	t_token	*collapsed_tokens;
	int		i;
	int		is_file;

	i = -1;
	is_file = 0;
	tokens = NULL;
	collapsed_tokens = NULL;
	if (!input)
		return (NULL);
	while (input[++i])
	{
		if (build_token(&tokens, input, &i, &is_file) == -1)
		{
			printf("msh: syntax error near unexpected token '%s'\n", input[i]);
			free_tokens(tokens);
			ft_free_arrays(input);
			return (NULL);
		}
	}
	sort_tokens(&tokens);
	build_collapsed_token(&collapsed_tokens, tokens);
	free_tokens(tokens);
	return (collapsed_tokens);
}
