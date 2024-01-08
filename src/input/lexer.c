/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:37:07 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/08 11:14:05 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_type type, char *value)
{
	t_token	*new_token;
	int		envvar;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->value = malloc(ft_strlen(value) + 1);
	envvar = strip_quotes(value, new_token->value);
	if (envvar == -1)
		return (NULL);
	else
		new_token->envvar = envvar;
	return (new_token);
}
/*
t_token	*create_token(t_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}*/

t_type	token_type(char *value)
{
	if (ft_strncmp(value, "|", 1) == 0)
		return (AST_PIPE);
	else if (ft_strncmp(value, "<<", 2) == 0)
		return (AST_HEREDOC);
	else if (ft_strncmp(value, "<", 1) == 0)
		return (AST_REDIRECT_IN);
	else if (ft_strncmp(value, ">", 1) == 0)
		return (AST_REDIRECT_OUT);
	return (AST_COMMAND);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	char	**split_input;
	char	*temp;
	char	*command;
	int		i;

	i = 0;
	split_input = split_cmd(input, " ");
	tokens = NULL;
	temp = NULL;
	while (split_input[i] != NULL)
	{
		if (token_type(split_input[i]) == AST_PIPE)
		{
			add_token_back(&tokens, create_token(AST_PIPE, split_input[i]));
			i++;
		}
		else if (token_type(split_input[i]) == AST_REDIRECT_IN)
		{
			add_token_back(&tokens, create_token(AST_REDIRECT_IN, split_input[i]));
			i++;
		}
		else if (token_type(split_input[i]) == AST_REDIRECT_OUT)
		{
			add_token_back(&tokens, create_token(AST_REDIRECT_OUT, split_input[i]));
			i++;
		}	
		else if (token_type(split_input[i]) == AST_HEREDOC)
		{
			add_token_back(&tokens, create_token(AST_HEREDOC, split_input[i]));
			i++;
			while (split_input[i] != NULL && ft_strlen(split_input[i]) == 0)
				i++;
			if (split_input[i] != NULL)
			{
				add_token_back(&tokens, create_token(AST_HEREDOC_DELIM,
					split_input[i]));
				i++;
			}
		}	
		else
		{
			command = ft_strdup(split_input[i]);
			i++;
			while (split_input[i] != NULL
				&& token_type(split_input[i]) == AST_COMMAND)
			{
				temp = command;
				command = ft_strjoin(command, " ");
				free(temp);
				temp = command;
				command = ft_strjoin(command, split_input[i]);
				free (temp);
				i++;
			}
			add_token_back(&tokens, create_token(AST_COMMAND, command));
			free(command);
		}
	}
	free(input);
	ft_free_arrays(split_input);
	return (tokens);
}
