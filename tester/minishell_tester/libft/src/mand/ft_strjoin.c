/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:57:26 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/06 22:49:46 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	joined = (char *)malloc(s1len + s2len + 1);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, s1len + 1);
	ft_strlcpy(joined + s1len, s2, s2len + 1);
	return (joined);
}

/*int	main(void)
{
	char *s1 = "Pablo";
	char *s2 = "Palma";

	printf("%s\n", ft_strjoin(s1, s2));
	return (0);
}*/
