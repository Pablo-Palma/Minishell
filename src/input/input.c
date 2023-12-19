/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:53:13 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/18 21:06:03 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input(t_minishell *shell, char *input) 
{
	t_token	*tokens = lexer(input);
	if (!tokens)
	{
		ft_printf("ERROR generating tokens");
		return (-1);
	}
	t_ast_node *ast = build_ast(tokens);
	if (!ast)
	{
		ft_printf("ERROR building AST");
		free_tokens(tokens);
		return (-1);
	}
	execute_ast_command(shell, ast);
	free_ast(ast);
	free_tokens(tokens);
	return(1);
}
