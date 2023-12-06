/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:11:06 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/06 11:11:24 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command_child(char **cmd_args, t_minishell *shell)
{
	char	*cmd_path;

	cmd_path = get_path(cmd_args[0], getenv("PATH"));
	if(!cmd_path)
		exit(EXIT_FAILURE);
	execve(cmd_path, cmd_args, shell->envp);
	ft_free_arrays(cmd_args);
	free(cmd_path);
		exit(EXIT_FAILURE);
}

void	execute_single_cmd(char **cmd_args, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		perror("Fork error");
	else if (pid == 0)
		execute_command_child(cmd_args, shell);
	else
	{
		waitpid(pid, &status, 0);
	}
}

void	execute_command(char *input, t_minishell *shell)
{
	char **cmd_args;

	cmd_args = split_cmd(input);
	if (!cmd_args)
		perror("Command not found");
	execute_single_cmd(cmd_args, shell);
	ft_free_arrays(cmd_args);
}
