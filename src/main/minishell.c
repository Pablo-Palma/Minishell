/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:21:06 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/06 20:57:04 by pabpalma         ###   ########.fr       */
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
			execute_command(input, &shell);
			free(input);
		}
		else
			free(input);
	}
	printf("Saliendo de minishell...\n");
	return (0);
}
