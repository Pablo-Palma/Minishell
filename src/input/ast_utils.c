/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:27:25 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/02 12:37:37 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_ast_node(t_type type, char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	return (node);
}

t_token	*get_last_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current->next)
		current = current->next;
	return (current);
}

int	add_token_back(t_token **head, t_token *new_token)
{
	t_token	*last;

	if (!head || !new_token)
		return (-1);
	if (*head)
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new_token;
		new_token->prev = last;
	}
	else
		*head = new_token;
	return (1);
}

int	add_ast_back(t_ast_node **head, t_ast_node *new_node)
{
	t_ast_node	*last;

	new_node->next = NULL;
	if (!head || !new_node)
		return (-1);
	if (*head == NULL)
	{
		new_node->prev = NULL;
		*head = new_node;
	}
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new_node;
		new_node->prev = last;
	}
	return (1);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	free(node->value);
	free(node);
}
