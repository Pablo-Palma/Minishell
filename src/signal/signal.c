/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:12:18 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/06 20:52:45 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t sigint_recived = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	
	sigint_recived = 1;
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	setup_signal_handlers()
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	
	sa.sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}
