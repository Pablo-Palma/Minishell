/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:11 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/26 13:38:44 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
	return (1);
}
/*
int	main(void)
{
//	char *str = "pablo";
//	ft_putchar_fd(*str, 1);
//	ft_putchar_fd(1, 1);
//	ft_putchar_fd('a', 1);
//	ft_putchar_fd('\t', 1);
	printf("%s\n", "primera salida: ");
	ft_putchar_fd(0, 1);
	printf("%s\n", "segunda salida: ");
	printf("%c", 0);
	printf("%s\n", "FIN");
	return (0);
}*/
