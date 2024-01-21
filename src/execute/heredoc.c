/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:45:29 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/17 20:47:37 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	proccess_heredoc(t_minishell *shell, char *delimiter)
{
	g_sigint_recived = SIGINT_HD;
	if (pipe(shell->pipes))
		handle_error("Error creating pipe", 1, EXIT_FAILURE);
	shell->fd_write = shell->pipes[1];
	shell->fd_read = shell->pipes[0];
	read_from_stdin(delimiter, shell->fd_write);
	close(shell->pipes[1]);
}

void	read_from_stdin(const char *delimiter, int write_fd)
{
	char	*line;

	while (1)
	{
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (!line || g_sigint_recived == SIGINT_RECIVED)
		{
			g_sigint_recived = SIGINT_HD_RECIVED;
			if (line)
				free(line);
			close(write_fd);
			break ;
		}
		if (strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write (write_fd, line, ft_strlen(line));
		free(line);
	}
}
