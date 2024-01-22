/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 23:49:08 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/22 23:49:52 by jbaeza-c         ###   ########.fr       */
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
