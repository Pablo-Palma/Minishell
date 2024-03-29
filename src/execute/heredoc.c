/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:45:29 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/05 13:36:10 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	proccess_heredoc(t_minishell *shell, char *delimiter)
{
	g_sigint_recived = SIGINT_HD;
	if (shell->hd_pipes)
	{
		shell->hd_pipes = shell->fd_write;
		shell->hd_pipes_read = shell->fd_read;
	}
	if (pipe(shell->pipes))
		handle_error("Error creating pipe", 1, EXIT_FAILURE);
	shell->fd_write = shell->pipes[1];
	shell->fd_read = shell->pipes[0];
	read_from_stdin(shell, delimiter, shell->fd_write);
	close(shell->pipes[1]);
	if (g_sigint_recived == SIGINT_HD_RECIVED)
		close(shell->pipes[0]);
	if (shell->hd_pipes)
	{
		shell->fd_write = shell->hd_pipes;
		execute_single_command(shell, shell->pipe_list->left->value);
	}
}

void	process_line(t_minishell *shell, char *line, int write_fd)
{
	while (ft_strchr(line, '$'))
		line = doc_envp(shell, line);
	write (write_fd, line, ft_strlen(line));
	if (line)
		free(line);
}

void	read_from_stdin(t_minishell *shell, const char *delim, int write_fd)
{
	char	*line;

	while (1)
	{
		signal(SIGQUIT, handle_sigquit);
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (!line || g_sigint_recived == SIGINT_RECIVED)
		{
			g_sigint_recived = SIGINT_HD_RECIVED;
			close (write_fd);
			if (line)
				free(line);
			break ;
		}
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0
			&& line[ft_strlen(delim)] == '\n')
		{
			free(line);
			break ;
		}
		process_line(shell, line, write_fd);
	}
}
