/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:27:38 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/07 12:58:23 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *src, int n)
{
	char	*dst;

	dst = (char *)malloc(n);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, src, n);
	return (dst);
}
