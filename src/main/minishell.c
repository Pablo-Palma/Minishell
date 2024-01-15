/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:21:06 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/15 15:56:24 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *shell, char **envp, char *executable_path)
{
	if (!shell)
		return ;
	shell->envp = envp;
	shell->og_envp = envp;
	shell->fd_read = 0;
	shell->fd_write = 1;
	shell->input_redirect = 0;
	shell->output_redirect = 0;
	shell->input_line = NULL;
	shell->ast = NULL;
	shell->last_cmd = 0;
	shell->last_exit_status = 0;
	shell->executable_path = ft_strdup(executable_path);
}

int	minishell(char **envp, char *executable_path)
{
	t_minishell	shell;
	char		*input;

	init_minishell(&shell, envp, executable_path);
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
			break ;
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
