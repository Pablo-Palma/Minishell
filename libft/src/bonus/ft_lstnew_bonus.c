/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:26:05 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/13 20:11:14 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}
/*
int	main(void)
{
	char coche[] = "Pablo Palma";
	t_list *node = ft_lstnew(coche);

	if(node)
	{
		printf("Content of the node: %s\n", (char *)node->content);
		printf("Content of the node: %s\n", (char *)node->next);
		free(node);
	}
	else
	printf("Failed to create node.\n");
	return (0);
}*/
