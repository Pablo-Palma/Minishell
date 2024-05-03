/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:08:39 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/02/06 21:19:41 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_redirections(t_minishell *shell)
{
	if (shell->output_redirect)
		shell->output_redirect = 0;
	if (shell->input_redirect)
		close(shell->fd_read);
}
