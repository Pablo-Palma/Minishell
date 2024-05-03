/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:04:42 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/27 12:47:54 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_fd(void *ptr, int fd)
{
	unsigned long	addr;
	char			*hex_str;
	int				len;

	addr = (unsigned long)ptr;
	hex_str = ft_itoa_base(addr, 16);
	if (!hex_str)
		return (-1);
	ft_putstr_fd("0x", fd);
	len = ft_putstr_fd(hex_str, fd) + 2;
	free(hex_str);
	return (len);
}
