/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 08:27:38 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/27 13:55:39 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsigned_fd(unsigned int n, int fd)
{
	char				c;
	int					count;
	long long unsigned	nb;

	count = 0;
	nb = (long long unsigned)n;
	if (nb > 9)
		count = ft_putunsigned_fd(nb / 10, fd);
	c = nb % 10 + '0';
	count += ft_putchar_fd(c, fd);
	return (count);
}
/*
int	main(void)
{
//	ft_putunsigned_fd(13, 1);
//	printf("\n");
//	ft_putunsigned_fd(-13, 1);
//	printf("\n");
//	ft_putunsigned_fd(-13, 1);
//	printf("\n");
//	printf("%d\n", ft_putunsigned_fd(-13, 1));
	printf("%d\n", ft_putunsigned_fd(1, 1));
	printf("\n");
	printf("%d\n", ft_putunsigned_fd(2, 1));
	printf("\n");
	printf("%d\n", ft_putunsigned_fd(-3, 1));
	printf("\n");
	printf("%u\n", -4294967296) // wrap-around
	printf("%u\n", -1) // underflow
	printf("%u\n", 4294967296) // overflow
	return (0);
}*/
