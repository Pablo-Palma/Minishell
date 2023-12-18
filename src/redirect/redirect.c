/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:24:33 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/13 14:10:27 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_redirect(t_minishell *shell, int pos)
{
	if (!strchr(shell->commands[pos], '<'))
		shell->input_redirect = NULL;
}

int	output_redirect(t_minishell *shell, int pos);
{
	if (!strchr(shell->commands[pos], '>'))
		shell->output_redirect = NULL;
}
