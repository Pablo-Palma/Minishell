/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:54:13 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/13 20:17:30 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
int main()
{
    t_list *head = ft_lstnew("Second");
    t_list *new_node = ft_lstnew("First");

    ft_lstadd_front(&head, new_node);
    while (head != NULL)
    {
        printf("%s\n", (char*)head->content);
        head = head->next;
    }
    return (0);
}*/
