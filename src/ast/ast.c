/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:32:58 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/10 10:43:21 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*build_ast(t_token *tokens)
{
	t_ast_node	*root;
	t_ast_node	*current;
	t_ast_node	*pipe_node;
	t_ast_node	*file;
	t_ast_node	*redirect_in;
	t_ast_node	*redirect_out;
	t_token		*token_iter;

	token_iter = tokens;
	root = NULL;
	file = NULL;
	redirect_in = NULL;
	redirect_out = NULL;
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
		else if (token_iter->type == AST_FILE)
			file = create_ast_node(token_iter->type, token_iter->value);
		else if (token_iter->type == AST_REDIRECT_IN)
		{
			redirect_in = create_ast_node(token_iter->type, token_iter->value);
			redirect_in->left = file;
		}
		else if (token_iter->type == AST_REDIRECT_OUT)
		{
			redirect_out = create_ast_node(token_iter->type, token_iter->value);
			redirect_out->left = file;
		}
		token_iter = token_iter->prev;
	}
	if (redirect_in)
	{
		if (root->type == AST_PIPE)
		{
			redirect_in->right = root->left;
			root->left = redirect_in;
		}
		else
		{
			redirect_in->right = root;
			root = redirect_in;
		}
	}
	if (redirect_out)
	{
		if (root->type == AST_COMMAND)
		{
			redirect_out->right = root;
			root = redirect_out;
		}
		else
		{
			current = root;
			while (current->right->right)
				current = current->right;
			redirect_out->right = current->right;
			current->right = redirect_out;
		}
	}
	return (root);
}
