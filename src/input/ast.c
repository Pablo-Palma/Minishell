/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:32:58 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/08 09:42:21 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_redirection(t_ast_node **root, t_ast_node **redirect)
{
	t_ast_node	*node;

	node = *root;
	if (!(*redirect))
		return ;
	if (!node)
		*root = *redirect;
	else if (node->type == AST_COMMAND || node->type == AST_REDIRECT_OUT)
	{
		(*redirect)->left = *root;
		*root = *redirect;
	}
	else
	{
		while (node->left && node->left->type == AST_HEREDOC)
			node = node->left;
		(*redirect)->left = node->left;
		(*root)->left = *redirect;
	}
	*redirect = NULL;
}

static void	set_tree(t_tree *tree)
{
	tree->root = NULL;
	tree->branch = NULL;
	tree->file = NULL;
	tree->red_in = NULL;
	tree->delim = NULL;
}

static void	build_tree(t_tree *tree, t_token *token)
{
	if (token->type == AST_FILE)
		tree->file = create_ast_node(token->type, token->value);
	else if (token->type == AST_HEREDOC_DELIM)
		tree->delim = create_ast_node(token->type, token->value);
	else if (token->type == AST_REDIRECT_IN && !tree->red_in)
		add_red_in(&tree->red_in, token, &tree->file);
	else if (token->type == AST_HEREDOC)
		add_hd(&tree->branch, token, &tree->delim);
	else if (token->type == AST_PIPE)
		add_pipe(&tree->branch, token);
	else if (token->type == AST_REDIRECT_OUT)
		add_red_out(&tree->branch, token, &tree->file);
	else if (token->type == AST_COMMAND || token->type == AST_SUBSHELL_EX)
		add_cmd(&tree->branch, token);
	else if (token->type == AST_AND || token->type == AST_OR)
		add_sequence(tree, token);
	else
	{
		if (tree->file)
			free_ast(tree->file);
	}
}

t_ast_node	*build_ast(t_token *tokens)
{
	t_tree		tree;
	t_token		*token_iter;
	t_ast_node	*node;

	token_iter = get_last_token(tokens);
	set_tree(&tree);
	while (token_iter)
	{
		if (token_iter->type == AST_PIPE && (!token_iter->next
				|| token_iter->next->type == AST_AND
				|| token_iter->next->type == AST_OR))
			return (free_ast(tree.root), free_ast(tree.branch),
				free_ast(tree.red_in));
		build_tree(&tree, token_iter);
		token_iter = token_iter->prev;
	}
	insert_redirection(&tree.branch, &tree.red_in);
	if (!tree.root)
		return (tree.branch);
	node = tree.root;
	while (node->left)
		node = node->left;
	node->left = tree.branch;
	return (tree.root);
}
