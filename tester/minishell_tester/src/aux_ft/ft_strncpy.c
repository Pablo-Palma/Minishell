/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:54:00 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/25 18:28:00 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strncpy(char *dst, const char *src, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dst[j])
		j++;
	while (src[i] && i < n)
		dst[j++] = src[i++];
	dst[j] = 0;
}
