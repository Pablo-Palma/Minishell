/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:04:24 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/06 22:43:27 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s2;

	size = ft_strlen(s1) + 1;
	s2 = (char *)malloc(size);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, size);
	return (s2);
}

/*int	main(void)
{
	const char *s1 = "lorem ipsum dolor sit amet";
	char *dup_str = ft_strdup(s1);

	printf("%s\n", dup_str);
	if (dup_str)
		free(dup_str);
	return (0);
}*/
