/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:34:21 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/05 20:58:20 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	if (argc == 1)
		minishell();
	else
		ft_printf("Incorrect input. Please, execute as follows: ./minishell\n");
	return (0);
}
