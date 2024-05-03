/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:28:46 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/19 09:28:49 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	char_to_find;

	char_to_find = (unsigned char)c;
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (char_to_find == 0)
		return ((char *)s);
	return (NULL);
}

/*int	main(void)
{
	char test[] = "Pablo Palma";

	printf("%s\n", ft_strchr(test, '\0'));
	return (0);
}*/
