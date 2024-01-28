/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:11:06 by pabpalma          #+#    #+#             */
/*   Updated: 2024/01/28 13:14:02 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_ast_command(t_minishell *shell, t_ast_node *node)
{
	if (node == NULL || shell == NULL)
	{
		perror("Nodo AST or Shell as NULL");
		return ;
	}
	if (node->type == AST_COMMAND)
		execute_single_command(shell, node->value);
	else if (node->type == AST_REDIRECT_OUT)
		execute_output_redirect(shell, node);
	else
		execute_pipe_cmd(shell, node);
}

void	execute_output_redirect(t_minishell *shell, t_ast_node *node)
{
	pid_t	pid;
	int		fd_out;

	node->right->value = strip_quotes(node->right->value);
	pid = fork();
	if (!pid)
	{
		if (ft_strncmp(node->value, ">>", 2) == 0)
			fd_out = open(node->right->value, O_WRONLY | O_CREAT
					| O_APPEND, 0777);
		else
			fd_out = open(node->right->value, O_WRONLY | O_CREAT
					| O_TRUNC, 0777);
		dup2(fd_out, STDOUT_FILENO);
		if (node->left)
			execute_single_command(shell, node->left->value);
		close(fd_out);
		exit(0);
	}
	waitpid(pid, 0, 0);
	return ;
}

void	execute_single_cmd_process(t_minishell *shell, char **args, char *path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		perror("Fork Error");
	else if (pid == 0)
	{
		if (args[1] && ft_strncmp(args[1], "$$", 3) == 0)
			exit (0);
		redirect_stdin(shell);
		if (execve(path, args, shell->envp) == -1)
			handle_error("Execve Error", 1, EXIT_FAILURE);
	}
	else
	{
		if (!shell->shell_pid)
			shell->shell_pid = ((int)pid - 1);
		if (args[1] && ft_strncmp(args[1], "$$", 3) == 0)
			printf("%d\n", shell->shell_pid);
		if (shell->fd_read != STDIN_FILENO)
			close(shell->fd_read);
		if (waitpid(pid, &status, 0) != -1 && WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
	}
}

int	handle_signal(t_minishell *shell, char *value)
{
	if (g_sigint_recived == SIGINT_HD_RECIVED)
	{
		shell->last_exit_status = 130;
		return (-1);
	}
	g_sigint_recived = SIGINT_COMMAND;
	if (!value || !shell)
		return (-1);
	return (0);
}

void	execute_single_command(t_minishell *shell, char *value)
{
	char	**args;
	char	*path;

	if (handle_signal(shell, value))
		return ;
	args = split_cmd(value, " ");
	if (!*args)
		return ;
	if (ft_strncmp(args[0], "./", 2) == 0)
		select_exec(shell, args);
	else if (!special_builtin(shell, args) && !handle_builtin(shell, args))
	{
		path = get_path(args[0], my_getenv(shell->envp, "PATH"));
		if (!path)
			exit_status(shell, args[0], 127);
		else
		{
			execute_single_cmd_process(shell, args, path);
			free(path);
		}
	}
	if (g_sigint_recived == SIGINT_RECIVED)
		shell->last_exit_status = 130;
	g_sigint_recived = SIGINT_NORMAL;
	ft_free_arrays(args);
}
