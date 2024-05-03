/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:06:46 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/23 17:25:07 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	length;
	int	written;

	if (!s)
		s = "(null)";
	length = ft_strlen(s);
	written = write(fd, s, length);
	if (written != length)
		return (-1);
	return (written);
}
/*
int	main(void)
{
	printf("%d\n", ft_putstr_fd("ABC\n", 1));
	printf("%d\n", ft_putstr_fd(NULL, 1));

//	ft_putstr_fd("cba", 2);
	return (0);
}*/
