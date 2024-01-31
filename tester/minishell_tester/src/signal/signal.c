/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:12:18 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/30 19:18:08 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>
#include <errno.h>

volatile sig_atomic_t	g_sigint_recived = SIGINT_NORMAL;

void	ignore_sigquit(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_sigquit(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigquit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_sigchild(int sig)
{
	int	saved_errno;

	(void)sig;
	saved_errno = errno;
	while (waitpid(-1, NULL, WNOHANG) > 0)
	{
	}
	errno = saved_errno;
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigquit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	if (g_sigint_recived == SIGINT_SUBSHELL)
	{
		sa.sa_handler = handle_sigchild;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_NOCLDSTOP | SA_RESTART;
		sigaction(SIGCHLD, &sa, NULL);
	}
}
