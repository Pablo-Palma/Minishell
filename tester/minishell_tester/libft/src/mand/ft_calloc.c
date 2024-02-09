/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:08:37 by pabpalma          #+#    #+#             */
/*   Updated: 2023/08/12 16:56:41 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*block;

	total_size = count * size;
	block = malloc(total_size);
	if (block)
		ft_memset(block, 0, total_size);
	return (block);
}
