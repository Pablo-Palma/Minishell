/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:32:58 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/17 21:02:22 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_redirection(t_ast_node **root, t_ast_node **redirect_in)
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

t_ast_node	*build_ast(t_token *tokens)
{
	t_ast_node	*root;
	t_ast_node	*file;
	t_ast_node	*redirect_in;
	t_token		*token_iter;

	token_iter = get_last_token(tokens);
	root = NULL;
	redirect_in = NULL;
	file = NULL;
	while (token_iter)
	{
		if (token_iter->type == AST_FILE)
			file = create_ast_node(token_iter->type, token_iter->value);
		if (token_iter->type == AST_REDIRECT_IN && !redirect_in)
			add_red_in(&redirect_in, token_iter, &file);
		if (token_iter->type == AST_PIPE)
			add_pipe(&root, token_iter);
		if (token_iter->type == AST_REDIRECT_OUT)
			add_red_out(&root, token_iter, &file);
		if (token_iter->type == AST_COMMAND)
			add_cmd(&root, token_iter);
		token_iter = token_iter->prev;
	}
	insert_redirection(&root, &redirect_in);
	return (root);
}
