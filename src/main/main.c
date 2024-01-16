/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:28:52 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/08 18:47:58 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*void leaks()
{
	system("leaks -q minishell");
}*/

int	main(int argc, char **argv, char **envp)
{
	//atexit(leaks);
	if (argc == 1)
		minishell(envp, argv[0]);
	else
		ft_printf("Incorrect input. Please, execute as follows: ./minishell\n");
	return (0);
}
