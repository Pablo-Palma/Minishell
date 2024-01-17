/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:45:29 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/08 18:45:07 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	proccess_heredoc(t_minishell *shell, char *delimiter)
{
	create_pipe(shell->pipes);
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
		if (!line)
			break ;
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
