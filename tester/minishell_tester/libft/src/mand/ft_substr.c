/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 23:48:55 by pabpalma          #+#    #+#             */
/*   Updated: 2023/08/16 01:11:51 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	s_len;
	char			*string;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	string = (char *)malloc(len + 1);
	if (!string)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		string[i] = s[start];
		start++;
		i++;
	}
	string[i] = '\0';
	return (string);
}

/*int	main(void)
{
	char *s = "Pablo Palma";
	unsigned int start = 6;
	size_t len = 5;
	char *substr;

	substr = ft_substr(s, start, len);
	printf("%s\n", substr);
	free(substr);
	return (0);
}*/
