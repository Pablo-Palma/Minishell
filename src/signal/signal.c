/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:12:18 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/30 08:02:07 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

volatile sig_atomic_t	g_sigint_recived = SIGINT_NORMAL;

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
	struct	sigaction sa;
	(void)sig;
	memset(&sa, 0, sizeof(sa));
	if (g_sigint_recived == SIGINT_COMMAND)
		write(1, "Quit: 3\n", 8);
	else
	{
		write(1, "wow_hd\n", 7);
	}
}

void	ignore_sigquit(void)
{
	struct	sigaction sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_sigquit(void)
{
	struct	sigaction sa;

	sa.sa_handler = handle_sigquit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
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
	
	/*sa.sa_handler = handle_sigchld;;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_NOCLDSOTP | SA_RESTART;;
	sigaction(SIGCHLD, &sa, NULL);*/
	
}
