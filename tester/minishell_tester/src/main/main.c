/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:28:52 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/07 16:56:51 by pabpalma         ###   ########.fr       */
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
	t_minishell	shell;

	if (argc == 1)
		minishell(envp);
	else if (argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
	{
		init_minishell(&shell, envp);
		handle_input(&shell, argv[2]);
		free_shell(&shell);
	}
	else
		ft_printf("Incorrect input. Please, execute as follows: ./minishell\n");
	return (0);
}
