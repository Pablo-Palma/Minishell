/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:37:07 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/15 15:34:18 by pabpalma         ###   ########.fr       */
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

t_token	*build_command_token(char **split_input, int *i)
{
	char		*command;
	char		*temp;
	t_token		*new_token;

	command = ft_strdup(split_input[*i]);
	if (!command)
		return (NULL);
	(*i)++;
	while (split_input[*i] != NULL && token_type(split_input[*i])
		== AST_COMMAND)
	{
		temp = command;
		command = ft_strjoin(command, " ");
		if (!command)
			return (NULL);
		free(temp);
		temp = command;
		command = ft_strjoin(command, split_input[*i]);
		if (!command)
			return (NULL);
		free(temp);
		(*i)++;
	}
	new_token = create_token(AST_COMMAND, command);
	free (command);
	return (new_token);
}

void	handle_heredoc(char **split_input, int *i, t_token	**tokens)
{
	add_token_back(tokens, create_token(AST_HEREDOC, split_input[*i]));
	(*i)++;
	while (split_input[*i] != NULL && ft_strlen(split_input[*i]) == 0)
		(*i)++;
	if (split_input[*i] != NULL)
	{
		add_token_back(tokens, create_token(AST_HEREDOC_DELIM,
				split_input[*i]));
		(*i)++;
	}
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	char	**split_input;
	t_token	*command_token;
	int		i;
	int		is_file;
	t_type	current_type;

	i = 0;
	is_file = 0;
	split_input = ft_split(input, ' ');
	tokens = NULL;
	while (split_input[i] != NULL)
	{
		current_type = token_type(split_input[i]);
		if (is_file)
		{
			add_token_back(&tokens, create_token(AST_FILE, split_input[i]));
			i++;
			is_file = 0;
		}
		else if (current_type == AST_PIPE || current_type == AST_REDIRECT_IN
			|| current_type == AST_REDIRECT_OUT)
		{
			add_token_back(&tokens, create_token(current_type, split_input[i]));
			is_file = (current_type != AST_PIPE);
			i++;
		}
		else if (current_type == AST_HEREDOC)
			handle_heredoc(split_input, &i, &tokens);
		else
		{
			command_token = build_command_token(split_input, &i);
			if (command_token)
				add_token_back(&tokens, command_token);
		}
	}
	free(input);
	ft_free_arrays(split_input);
	return (tokens);
}
