/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:23:29 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/08 14:00:57 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_type(t_token *token)
{
	if (token->type == AST_PIPE)
		return (1);
	if (token->type == AST_AND)
		return (1);
	if (token->type == AST_OR)
		return (1);
	return (0);
}

t_token	*check_pipes(t_token **root)
{
	t_token	*token;

	token = *root;
	while (token && token->prev)
		token = token->prev;
	*root = token;
	while (token)
	{
		if (token->type == AST_PIPE)
		{
			if (!token->prev || !token->next || check_type(token->prev)
				|| check_type(token->next))
			{
				printf("msh: syntax error: near unexpected token %s\n",
					token->value);
				free_tokens(*root);
				return (NULL);
			}
		}
		token = token->next;
	}
	return (*root);
}
