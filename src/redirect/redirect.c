/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:24:33 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/21 16:56:59 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	input_redirect(t_minishell *shell, int pos)
{
	if (!strchr(shell->commands[pos], '<'))
		shell->input_redirect = NULL;
}
*/
int	input_redirection(t_minishell *shell, t_ast_node *cmd_node)
{
	close(shell->fd_read);
	shell->fd_read = open(cmd_node->value, O_RDONLY, 0777);
	if (shell->input_redirect == -1)
		return (-1);
	return (1);
}

int	here_doc(t_minishell *shell, t_ast_node *cmd_node)
{
	(void)shell;
	(void)cmd_node;
	return (1);
}

int	output_redirection(t_minishell *shell, t_ast_node *cmd_node)
{
	close(shell->fd_write);
	shell->fd_write = open(cmd_node->value,
		O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (shell->output_redirect == -1)
		return (-1);
	return (1);
}

int	output_append_redirection(t_minishell *shell, t_ast_node *cmd_node)
{
	close(shell->fd_write);
	shell->fd_write = open(cmd_node->value,
		O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (shell->output_redirect == -1)
		return (-1);
	return (1);
}

int	handle_redirect(t_minishell *shell, t_ast_node *cmd_node)
{
	if (ft_strncmp(cmd_node->value, "<<", 2) == 0)
		here_doc(shell, cmd_node->left);
	if (ft_strncmp(cmd_node->value, ">>", 2) == 0)
		output_append_redirection(shell, cmd_node->left);
	if (ft_strncmp(cmd_node->value, "<", 1) == 0)
		input_redirection(shell, cmd_node->left);
	if (ft_strncmp(cmd_node->value, ">", 1) == 0)
		output_redirection(shell, cmd_node->left);
	return (1);
}