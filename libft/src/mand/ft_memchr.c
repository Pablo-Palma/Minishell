/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:57:56 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/19 09:58:41 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	value;

	ptr = (unsigned char *)s;
	value = (unsigned char)c;
	while (n--)
	{
		if (*ptr == value)
			return (ptr);
		ptr++;
	}
	return (NULL);
}

/*int	main(void)
{
	char *s = "Pablo Palma";
	char *res = (char *) ft_memchr(s, 'b', 5);

	if (res)
		printf("Primera 'b' encontrada en: %s\n", res);
	else
		printf("'b' no encontrada en los primeros 5 caracteres");
	return (0);
}*/
