/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:32:58 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/18 11:30:53 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*build_ast(t_token *tokens)
{
	t_ast_node	*root;
	t_ast_node	*current;
	t_ast_node	*pipe_node;
	t_token		*token_iter;

	token_iter = tokens;
	root = NULL;
	current = NULL;
	while (token_iter->next)
		token_iter = token_iter->next;
	if (!tokens)
		return (NULL);
	while (token_iter)
	{
		if (token_iter->type == AST_COMMAND)
		{
			current = create_ast_node(token_iter->type, token_iter->value);
			if (!root)
				root = current;
			else
				root->left = current;
		}
		else if (token_iter->type == AST_PIPE)
		{
			pipe_node = create_ast_node(token_iter->type, token_iter->value);
			pipe_node->right = root;
			root = pipe_node;
		}
		token_iter = token_iter->prev;
	}
	return (root);
}
