/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:55:36 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/19 10:56:35 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + str[i] - '0';
		i++;
	}
	return (sign * nb);
}

/*int	main(void)
{

	printf("%d\n", ft_atoi(" --+-----+-+-1234567"));
	printf("%d\n", atoi(" --+-----+-+-1234567"));
	printf("%d\n", ft_atoi("123"));         // Esperado: 123
	printf("%d\n", ft_atoi("-123"));        // Esperado: -123
	printf("%d\n", ft_atoi("    +123abc")); // Esperado: 123
	printf("%d\n", ft_atoi("  -+123"));     // Esperado: 0


	return (0);
}*/
