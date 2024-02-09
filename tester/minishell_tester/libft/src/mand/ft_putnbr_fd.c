/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:32:45 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/26 13:24:49 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		nlen;

	nlen = 0;
	if (n == INT_MIN)
	{
		write (fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		nlen += ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
		nlen += ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	nlen += ft_putchar_fd(c, fd);
	return (nlen);
}
/*
int	main(void)
{
	int n = INT_MIN;
	int fd = 1;

	printf("%d\n", ft_putnbr_fd(n, fd));
	printf("%s\n", "--------------------");
	printf("%d\n", ft_putnbr_fd(-103, 1));
	return (0);
}*/
