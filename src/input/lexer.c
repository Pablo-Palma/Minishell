/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:37:07 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/18 11:34:00 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

t_type	token_type(char *value)
{
	if (ft_strncmp(value, "|", 1) == 0)
		return (AST_PIPE);
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
		if (token_type(split_input[i]) != AST_COMMAND)
		{
			add_token_back(&tokens, create_token(AST_PIPE, split_input[i]));
			i++;
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
	ft_free_arrays(split_input);
	return (tokens);
}
