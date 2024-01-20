/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:12:18 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/08 18:47:03 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

volatile sig_atomic_t	g_sigint_recived = 0;

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
	g_sigint_recived = 1;
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}
