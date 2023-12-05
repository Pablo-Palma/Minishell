/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:34:21 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/05 19:40:08 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		minishell(argv, envp);
	else
		ft_printf("Incorrect input. Please, execute as follows: ./minishell\n");
	return (0);
}
