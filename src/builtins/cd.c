/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:46:52 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/07 09:10:39 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//chdir changes the working directory to the one specified by
//the argument recived as a string. If chdir works correctly, it returns 0.
//Otherwise, if chdir fails, it return -1. to understand the reason for
//the failure, we use perror, which prints a descreiptive error message based
//on the current calue of errno.

void	cd_command(char **cmd_args)
{
	char	*path;

	path = cmd_args[1];
	if (path == NULL)
		path = getenv("HOME");
	if (chdir(path) != 0)
		perror("cd");
}
