/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:09:58 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/19 09:10:03 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t	dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize == 0 || dstsize <= dstlen)
		return (dstsize + srclen);
	while (src[i] != 0 && (dstlen + i) < dstsize -1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	if (dstlen + i < dstsize)
		dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}

/*int	main(void)
{
	char dst[10] = "a";
//	char src[] = "Palma";

	printf("%zu\n", ft_strlcat(dst, "lorem ipsum dolor sit amet", 0));
	printf("%zu\n", strlcat(dst, "lorem ipsum dolor sit amet", 0));
	return (0);
}*/
