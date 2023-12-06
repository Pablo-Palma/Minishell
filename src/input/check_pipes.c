/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:42:00 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/06 15:02:48 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

int	is_non_pipe_cmd(char *cmd)
{
	int	i;

	i = 0;
	if (!ft_strncmp(cmd, "cd", 3))
		i = 1;
	else if (!ft_strncmp(cmd, "export", 7))
		i = 1;
	else if (!ft_strncmp(cmd, "unset", 6))
		i = 1;
	else if (!ft_strncmp(cmd, "exit", 5))
		i = 1;
	free(cmd);
	return (i);
}
