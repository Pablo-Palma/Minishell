/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:32:58 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/31 15:16:06 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_redirection(t_ast_node **root, t_ast_node **redirect_in)
{
	if (!(*redirect_in))
		return ;
	if (!(*root))
		*root = *redirect_in;
	else if ((*root)->type == AST_COMMAND)
	{
		(*redirect_in)->left = *root;
		*root = *redirect_in;
	}
	else
	{
		(*redirect_in)->left = (*root)->left;
		(*root)->left = *redirect_in;
	}
}

static void	set_tree(t_tree *tree)
{
	tree->root = NULL;
	tree->real_root = NULL;
	tree->branch = NULL;
	tree->file = NULL;
	tree->red_in = NULL;
}

t_ast_node	*build_ast(t_token *tokens)
{
	t_tree	tree;
	t_token	*token_iter;

	token_iter = get_last_token(tokens);
	set_tree(&tree);
	while (token_iter)
	{
		if (token_iter->type == AST_FILE)
			tree.file = create_ast_node(token_iter->type, token_iter->value);
		else if (token_iter->type == AST_REDIRECT_IN && !tree.red_in)
			add_red_in(&tree.red_in, token_iter, &tree.file);
		else if (token_iter->type == AST_PIPE)
			add_pipe(&tree.branch, token_iter);
		else if (token_iter->type == AST_REDIRECT_OUT)
			add_red_out(&tree.branch, token_iter, &tree.file);
		else if (token_iter->type == AST_COMMAND || token_iter->type == AST_SUBSHELL_EX)
			add_cmd(&tree.branch, token_iter);
		else
			add_sequence(&tree, token_iter);
		token_iter = token_iter->prev;
	}
	if (!tree.root)
		return (tree.branch);
	tree.root->left = tree.branch;
	return (tree.real_root);
}
