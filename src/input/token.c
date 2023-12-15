/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:17:03 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/15 12:14:34 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_token(t_token **head, t_token *new_token)
{
	t_token	*node;

	node = *head;
	if (!node)
		node = new_token;
	else
	{
		while(node->next)
			node = node->next;
		node->next = new_token;
	}
	return (1);
}

t_token	*create_token(char	*data)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	node->data = ft_strdup(data);
	node->next = NULL;
	return(node);
}

int	tokenize(char *input)
{
	char	**token_lst;
	int		i;

	token_lst = command_split(input, " ");
	i = -1;
	while (token_lst[++i])
		add_token(&shell->tokens, create_token(token_lst[i]));
	ft_free_arrays(token_lst);
	return (1);
}
