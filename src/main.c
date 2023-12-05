/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:21:06 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/05 16:59:04 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	char	**args;
	char	*cmd_path;
	while (1)
	{
		input = readline("minishell> ");
	
		if (!input)
			break;
		if (*input)
		{
			add_history(input);
			args = split_cmd(input);
			cmd_path = get_path(args[0], getenv("PATH"));
			printf("%s\n", cmd_path);
			free(cmd_path);
			ft_free_arrays(args);
		}
		free(input);
	}
	printf("Saliendo de minishell...\n");
	return (0);
}
