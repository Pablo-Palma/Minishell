/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:35:26 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/02/02 18:41:41 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd(t_ast_node **root, t_token *token)
{
	t_ast_node	*cmd;
	t_ast_node	*node;

	cmd = create_ast_node(token->type, token->value);
	node = *root;
	if (!node)
		(*root) = cmd;
	else
	{
		while (node->left)
			node = node->left;
		node->left = cmd;
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
	t_ast_node	*node;

	node = *root;
	redirect = create_ast_node(token->type, token->value);
	if (*file)
		redirect->right = (*file);
	*file = NULL;
	if (!node)
		*root = redirect;
	else if (node->type == AST_COMMAND)
	{
		redirect->left = (*root);
		(*root) = redirect;
	}
	else
	{
		while (node->left && node->left != AST_COMMAND)
			node = node->left;
		redirect->left = node->left;
		node->left = redirect;
	}
}

void	add_hd(t_ast_node **root, t_token *token, t_ast_node **delim)
{
	t_ast_node	*hd;

	hd = create_ast_node(token->type, token->value);
	if (*delim)
		hd->right = (*delim);
	*delim = NULL;
	if (!(*root))
		(*root) = hd;
	else if ((*root)->type == AST_PIPE)
	{
		hd->left = (*root)->left;
		(*root)->left = hd;
	}
	else
	{
		hd->left = (*root);
		(*root) = hd;
	}
}

void	add_red_in(t_ast_node **root, t_token *token, t_ast_node **file)
{
	(*root) = create_ast_node(token->type, token->value);
	if (*file)
		(*root)->right = (*file);
	*file = NULL;
}
