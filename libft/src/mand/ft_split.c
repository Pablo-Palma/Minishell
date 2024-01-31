/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:09:28 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/19 13:27:03 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char c, char const charset)
{
	return (c == charset);
}

static int	count_words(char const *str, char const charset)
{
	int	words;

	words = 0;
	while (*str)
	{
		while (*str && is_sep(*str, charset))
			str++;
		if (*str && !is_sep(*str, charset))
		{
			words++;
			while (*str && !is_sep(*str, charset))
				str++;
		}
	}
	return (words);
}

static char	*ft_strdupp(char const *src, char const *end)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (src + len != end)
		len++;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while (src + i < end)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *str, char const charset)
{
	char		**result;
	char const	*start;
	int			words;
	int			i;

	words = count_words(str, charset);
	i = 0;
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	while (i < words)
	{
		while (*str && is_sep(*str, charset))
			str++;
		if (*str && !is_sep(*str, charset))
		{
			start = str;
			while (*str && !is_sep(*str, charset))
				str++;
			result[i] = ft_strdupp(start, str);
			i++;
		}
	}
	result[i] = NULL;
	return (result);
}

/*int	main(void)
{
	const char str[] = "Pablo Palma";
	const char charset = ' ';
	char **words = ft_split(str, charset);
	int i = 0;

	while (words[i] != NULL)
	{
		printf("%s\n", words[i]);
		free (words[i]);
		i++;
	}
	free (words);
	return (0);
}*/
