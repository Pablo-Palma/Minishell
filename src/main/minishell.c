/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:21:06 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/18 21:08:42 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *shell, char **envp)
{
	if (!shell)
		return ;
	shell->envp = envp;
	shell->fd_read = 0;
	shell->fd_write = 1;
	shell->input_redirect = 0;
	shell->output_redirect = 0;
	shell->input_line = NULL;
	shell->ast = NULL;
	shell->last_cmd = 1;
}

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
		{
			g_sigint_recived = 0;
		}
		if (!input)
		{
			ft_printf("%s\n", "EOF recibido. Saliendo...\n");
			break;
		}
		if (*input)
		{
			add_history(input);
			handle_input(&shell, input);
			free(input);
		}
		else
			free(input);
	}
	printf("Saliendo de minishell...\n");
	return (0);
}
