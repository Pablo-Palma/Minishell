/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:45:56 by pabpalma          #+#    #+#             */
/*   Updated: 2023/09/26 15:05:42 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	typeflag(va_list *content, const char identifier)
{
	if (identifier == 'c')
		return (ft_putchar_fd(va_arg(*content, int), 1));
	else if (identifier == 's')
		return (ft_putstr_fd(va_arg(*content, char *), 1));
	else if (identifier == 'p')
		return (ft_putptr_fd(va_arg(*content, void *), 1));
	else if (identifier == 'd' || identifier == 'i')
		return (ft_putnbr_fd(va_arg(*content, int), 1));
	else if (identifier == 'u')
		return (ft_putunsigned_fd(va_arg(*content, unsigned int), 1));
	else if (identifier == 'x')
		return (ft_puthexlo_fd(va_arg(*content, unsigned long), 1));
	else if (identifier == 'X')
		return (ft_puthexup_fd(va_arg(*content, unsigned long), 1));
	else
		return (0);
}

int	ft_printf(char const *str, ...)
{
	va_list	vargs;
	int		charcount;

	charcount = 0;
	va_start(vargs, str);
	while (*str != 0)
	{
		if (*str == '%')
		{
			if (*(++str) != '%')
				charcount += typeflag(&vargs, *str);
			else
				charcount += ft_putchar_fd(*str, 1);
		}
		else
			charcount += ft_putchar_fd(*str, 1);
		str++;
	}
	va_end(vargs);
	return (charcount);
}
