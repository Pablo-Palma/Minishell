/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 23:49:08 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/27 12:56:16 by jbaeza-c         ###   ########.fr       */
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
	new_token->envvar = 0;
	new_token->value = ft_strdup(value);
	envvar = open_quotes(value);
	if (envvar == -1)
	{
		free(new_token->value);
		free(new_token);
		return (NULL);
	}
	if (type == AST_FILE)
		return (new_token);
	new_token->envvar = envvar;
	return (new_token);
}

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
