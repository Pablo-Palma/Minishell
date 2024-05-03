/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_baseup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:38:33 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/26 12:13:30 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	stringlen(unsigned long value, int base)
{
	int	len;

	len = 0;
	if (value == 0)
		return (1);
	while (value)
	{
		value = value / base;
		len++;
	}
	return (len);
}

char	*ft_itoa_baseup(unsigned long value, int base)
{
	static char		dict[] = "0123456789ABCDEF";
	char			*result;
	int				len;

	if (base < 2 || base > 16)
		return (NULL);
	len = stringlen(value, base);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	if (value == 0)
	{
		result[0] = '0';
		result[1] = '\0';
	}
	else
	{
		result[len] = '\0';
		while (len--)
		{
			result[len] = dict[value % base];
			value = value / base;
		}
	}
	return (result);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa_base(255, 16));
	printf("%s\n", ft_itoa_base(0, 16));
	return (0);
}*/
