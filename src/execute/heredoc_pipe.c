/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:26:12 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/02/02 18:28:01 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_line_hd(t_minishell *shell, char *line)
{
	while (strchr(line, '$'))
		line = doc_envp(shell, line);
	printf("%s", line);
	if (line)
		free(line);
}

void	read_from_stdin_hd(t_minishell *shell, const char *delim)
{
	char	*line;

	while (1)
	{
		signal(SIGQUIT, handle_sigquit);
		line = get_next_line(STDIN_FILENO);
		if (!line || g_sigint_recived == SIGINT_RECIVED)
		{
			g_sigint_recived = SIGINT_HD_RECIVED;
			if (line)
				free(line);
			break ;
		}
		if (strncmp(line, delim, ft_strlen(delim)) == 0
			&& line[ft_strlen(delim)] == '\n')
		{
			free(line);
			break ;
		}
		process_line_hd(shell, line);
	}
}

void	process_hd_pipe(t_minishell *shell, char *delimiter)
{
	g_sigint_recived = SIGINT_HD;
	read_from_stdin_hd(shell, delimiter);
	if (g_sigint_recived == SIGINT_HD_RECIVED)
		close(shell->pipes[0]);
}
