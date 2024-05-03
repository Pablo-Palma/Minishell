/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:15:15 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/15 09:40:23 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*void	ft_simple_delete(void *content)
{
	free(content);
}*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
