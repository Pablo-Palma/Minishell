/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:10:57 by pabpalma          #+#    #+#             */
/*   Updated: 2023/08/24 16:15:13 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*result;
	const char	*start;
	const char	*end;
	char		*tmp;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	while (*start && ft_is_in_set(*start, set))
		start++;
	end = s1 + ft_strlen(s1);
	while (end > start && ft_is_in_set(*(end - 1), set))
		end--;
	result = (char *)malloc(end - start + 1);
	if (!result)
		return (NULL);
	tmp = result;
	while (start < end)
		*tmp++ = *start++;
	*tmp = '\0';
	return (result);
}

/*int	main(void)
{
	char *s1 = "eePablo Palmaee";
	char *set  = "e";

	printf("%s\n", ft_strtrim(s1, set));
	return (0);
}*/
