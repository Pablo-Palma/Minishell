/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexup_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:56:03 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/26 12:14:25 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexup_fd(unsigned int n, int fd)
{
	char			*hex_str;
	unsigned long	nb;
	int				len;

	nb = (unsigned long)n;
	hex_str = ft_itoa_baseup(nb, 16);
	if (!hex_str)
		return (-1);
	ft_putstr_fd(hex_str, fd);
	len = ft_strlen(hex_str);
	free(hex_str);
	return (len);
}
/*
int	main(void)
{
	ft_puthexup_fd(0, 1);
	return (0);
}*/
