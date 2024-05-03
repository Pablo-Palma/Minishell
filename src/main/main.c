/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:28:52 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/08 11:54:38 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
void	leaks(void)
{
	system("leaks -q minishell");
}
*/

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
		minishell(envp);
	else
		ft_printf("Incorrect input. Please, execute as follows: ./minishell\n");
	return (0);
}
