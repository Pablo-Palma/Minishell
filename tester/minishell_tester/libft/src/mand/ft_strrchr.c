/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:32:31 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/19 09:35:41 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_ocurrence;
	char	char_to_find;

	last_ocurrence = NULL;
	char_to_find = (unsigned char) c;
	while (*s)
	{
		if (*s == char_to_find)
			last_ocurrence = (char *)s;
		s++;
	}
	if (char_to_find == '\0')
		return ((char *)s);
	return (last_ocurrence);
}
