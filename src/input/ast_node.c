/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:35:26 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/23 00:24:01 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd(t_ast_node **root, t_token *token)
{
	if (!(*root))
		(*root) = create_ast_node(token->type, token->value);
	else
	{
		if (!(*root)->left)
			(*root)->left = create_ast_node(token->type, token->value);
		else
			(*root)->left->left = create_ast_node(token->type, token->value);
	}
}

void	add_pipe(t_ast_node **root, t_token *token)
{
	t_ast_node	*pipe;

	pipe = create_ast_node(token->type, token->value);
	pipe->right = (*root);
	(*root) = pipe;
}

void	add_red_out(t_ast_node **root, t_token *token, t_ast_node **file)
{
	t_ast_node	*redirect;

	redirect = create_ast_node(token->type, token->value);
	redirect->right = (*file);
	if (!(*root))
		(*root) = redirect;
	else if ((*root)->type == AST_PIPE)
	{
		redirect->left = (*root)->left;
		(*root)->left = redirect;
	}
	else
	{
		redirect->left = (*root);
		(*root) = redirect;
	}
}

void	add_red_in(t_ast_node **root, t_token *token, t_ast_node **file)
{
	(*root) = create_ast_node(token->type, token->value);
	(*root)->right = (*file);
}
