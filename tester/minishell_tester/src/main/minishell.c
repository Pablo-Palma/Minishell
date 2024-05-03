/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:21:06 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/30 10:59:04 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **envp)
{
	t_minishell	shell;
	char		*input;

	init_minishell(&shell, envp);
	while (1)
	{
		setup_signal_handlers();
		ignore_sigquit();
		input = readline("minishell> ");
		if (g_sigint_recived)
			g_sigint_recived = SIGINT_NORMAL;
		if (!input)
		{
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
	return (0);
}
