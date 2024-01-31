/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:32:58 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/31 20:01:10 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_redirection(t_ast_node **root, t_ast_node **redirect)
{
	if (!(*redirect))
		return ;
	if (!(*root))
		*root = *redirect;
	else if ((*root)->type == AST_COMMAND)
	{
		(*redirect)->left = *root;
		*root = *redirect;
	}
	else
	{
		(*redirect)->left = (*root)->left;
		(*root)->left = *redirect;
	}
	*redirect = NULL;
}

static void	set_tree(t_tree *tree)
{
	tree->root = NULL;
	tree->real_root = NULL;
	tree->branch = NULL;
	tree->file = NULL;
	tree->red_in = NULL;
	tree->hd = NULL;
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
	else if (token->type == AST_HEREDOC && !tree->hd)
		add_red_in(&tree->hd, token, &tree->delim);
	else if (token->type == AST_PIPE)
		add_pipe(&tree->branch, token);
	else if (token->type == AST_REDIRECT_OUT)
		add_red_out(&tree->branch, token, &tree->file);
	else if (token->type == AST_COMMAND || token->type == AST_SUBSHELL_EX)
		add_cmd(&tree->branch, token);
	else
		add_sequence(tree, token);
}

t_ast_node	*build_ast(t_token *tokens)
{
	t_tree	tree;
	t_token	*token_iter;

	token_iter = get_last_token(tokens);
	set_tree(&tree);
	while (token_iter)
	{
		build_tree(&tree, token_iter);
		token_iter = token_iter->prev;
	}
	insert_redirection(&tree.branch, &tree.red_in);
	insert_redirection(&tree.branch, &tree.hd);
	if (!tree.root)
		return (tree.branch);
	tree.root->left = tree.branch;
	return (tree.real_root);
}
