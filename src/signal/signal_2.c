/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:54:15 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/02/08 12:24:00 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>
#include <errno.h>

void	exit_status(t_minishell *shell, const char *msg, int status)
{
	perror(msg);
	shell->last_exit_status = status;
}

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_sigint_recived == SIGINT_HD)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ioctl(0, TIOCSTI, "\n");
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_sigint_recived != SIGINT_COMMAND)
			rl_redisplay();
	}
	g_sigint_recived = SIGINT_RECIVED;
}

void	handle_sigquit(int sig)
{
	struct sigaction	sa;

	(void)sig;
	ft_memset(&sa, 0, sizeof(sa));
	if (g_sigint_recived == SIGINT_COMMAND)
	{
		write(1, "Quit: 3\n", 8);
		g_sigint_recived = SIGQUIT_COMMAND;
	}
	else if (g_sigint_recived == SIGINT_HD)
		ignore_sigquit();
}
