/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 00:28:50 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/02/07 13:21:27 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_and_sequence(t_minishell *shell, t_ast_node *node)
{
	execute_ast_command(shell, node->left);
	if (!shell->last_exit_status)
		execute_ast_command(shell, node->right);
}

void	add_pipe(t_ast_node **root, t_token *token)
{
	t_ast_node	*pipe;

	pipe = create_ast_node(token->type, token->value);
	pipe->right = (*root);
	(*root) = pipe;
}

void	execute_heredoc(t_minishell*shell, t_ast_node *node)
{
	if (!node->right)
	{
		printf("msh: syntax error: no delimiter for here_doc\n");
		return ;
	}
	if (!node->left)
	{
		printf("msh: syntax error: no command for here_doc\n");
		return ;
	}
	proccess_heredoc(shell, node->right->value);
	if (shell->hd_pipes != 1)
		execute_ast_command(shell, node->left);
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

void	single_cmd_process(t_minishell *shell, char **args, char *path)
{
	pid_t	pid;
	int		status;

	setup_signal_handlers();
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
	if (!shell->shell_pid)
		shell->shell_pid = ((int)pid - 1);
	if (args[1] && ft_strncmp(args[1], "$$", 3) == 0)
		printf("%d\n", shell->shell_pid);
	if (shell->fd_read != STDIN_FILENO)
		close(shell->fd_read);
	if (shell->hd_pipes_read)
		shell->fd_read = shell->hd_pipes_read;
	if (waitpid(pid, &status, 0) != -1 && WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
}
