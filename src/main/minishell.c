/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:21:06 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/18 15:58:53 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **envp)
{
	t_minishell	shell;
	char		*input;

	init_minishell(&shell, envp);
	setup_signal_handlers();
	while (1)
	{
		input = readline("minishell> ");
		if (g_sigint_recived)
			g_sigint_recived = SIGINT_NORMAL;
		if (!input)
		{
			ft_printf("%s\n", "EOF recibido.");
			free_shell(&shell);
			free(input);
			break ;
		}
		if (*input)
		{
			add_history(input);
			handle_input(&shell, input);
		}
		free(input);
	}
	printf("Saliendo de minishell...\n");
	return (0);
}
