/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:21:06 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/08 21:06:09 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **envp)
{
	t_minishell	shell;
	char		*input;

	shell.envp = envp;
	setup_signal_handlers();
	while (1)
	{
		input = readline("minishell> ");
	
		if (sigint_recived)
		{
			sigint_recived = 0;
			printf("\nminishell> ");
		}
		if (!input)
		{
			ft_printf("%s\n", "EOF recibido. Saliendo...\n");
			break;
		}
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break;
		}
		if (*input)
		{
			add_history(input);
			handle_input(input, &shell);
			free(input);
		}
		else
			free(input);
	}
	printf("Saliendo de minishell...\n");
	return (0);
}
