/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:24:33 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/02/06 21:07:36 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_stdin(t_minishell *shell)
{
	if (shell->fd_read != STDIN_FILENO)
	{
		dup2(shell->fd_read, STDIN_FILENO);
		close(shell->fd_read);
	}
	if (shell->hd_pipes)
	{
		if (shell->fd_write != STDOUT_FILENO)
		{
			dup2(shell->fd_write, STDOUT_FILENO);
			close(shell->fd_write);
		}
	}
}

int	input_redirection(t_minishell *shell, t_ast_node *cmd_node)
{
	shell->fd_read = open(cmd_node->value, O_RDONLY, 0777);
	if (shell->fd_read == -1)
		return (-1);
	shell->input_redirect = 1;
	return (1);
}

int	output_redirection(t_minishell *shell, t_ast_node *cmd_node)
{
	if (shell->output_redirect && shell->fd_write != STDOUT_FILENO)
		close(shell->fd_write);
	shell->fd_write = open(cmd_node->value,
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (shell->fd_write == -1)
		return (-1);
	shell->output_redirect = 1;
	return (1);
}

int	output_append_redirection(t_minishell *shell, t_ast_node *cmd_node)
{
	if (shell->output_redirect && shell->fd_write != STDOUT_FILENO)
		close(shell->fd_write);
	shell->fd_write = open(cmd_node->value,
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (shell->fd_write == -1)
		return (-1);
	shell->output_redirect = 1;
	return (1);
}

int	handle_redirect(t_minishell *shell, t_ast_node *cmd_node)
{
	int	status;

	status = 0;
	if (!cmd_node->right)
		return (-1);
	if (ft_strncmp(cmd_node->value, ">>", 2) == 0)
		status = output_append_redirection(shell, cmd_node->right);
	else if (ft_strncmp(cmd_node->value, "<", 1) == 0)
		status = input_redirection(shell, cmd_node->right);
	else if (ft_strncmp(cmd_node->value, ">", 1) == 0)
		status = output_redirection(shell, cmd_node->right);
	return (status);
}
