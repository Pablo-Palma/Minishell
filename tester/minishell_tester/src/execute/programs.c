/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:45:38 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/02/02 16:54:41 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_subshell_ex(t_minishell *shell, char *sub_expr, int is_pipe)
{
	pid_t	pid;
	int		status;
	char	*args[4];

	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = sub_expr;
	args[3] = NULL;
	pid = fork();
	status = 0;
	signal(SIGINT, SIG_IGN);
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (is_pipe)
			dup2(shell->pipes[1], STDOUT_FILENO);
		increment_shlvl(shell);
		if (execve("/bin/sh", args, shell->og_envp) == -1)
			handle_error("minishell: expr command error", 1, -1);
	}
	waitpid(pid, &status, 0);
	shell->last_exit_status = WEXITSTATUS(status);
}

void	execute_subshell(t_minishell *shell, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	signal(SIGINT, SIG_IGN);
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		increment_shlvl(shell);
		if (execve(args[0], args, shell->og_envp) == -1)
		{
			perror ("execve");
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	g_sigint_recived = SIGINT_NORMAL;
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
}

void	execute_program(t_minishell *shell, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == 0)
	{
		if (execve(args[0], args, shell->envp) == -1)
		{
			perror("Execve Error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (shell->fd_read != STDIN_FILENO)
			close(shell->fd_read);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
	}
}

void	select_exec(t_minishell *shell, char **command)
{
	if (command == NULL)
		return ;
	if (ft_strncmp(command[0], "./minishell", 11) == 0)
		execute_subshell(shell, command);
	else
		execute_program(shell, command);
}
