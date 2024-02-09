/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:03:27 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/18 12:04:44 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	sust;
	unsigned int	i;

	ptr = (unsigned char *)b;
	sust = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		ptr[i] = sust;
		i++;
	}
	return (b);
}
