/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:11:06 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/16 15:45:42 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_ast_command(t_ast_node *node, t_minishell *shell)
{
	if (node == NULL || shell == NULL)
	{
		perror("Nodo AST or Shell as NULL");
		return ;
	}
	if (node->type == AST_COMMAND)
		execute_single_command(node->value, shell);
	if (node->type == AST_PIPE)
		execute_ast_pipe(node, shell);
}

void	execute_single_command(char *value, t_minishell *shell)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**args;

	if (!value || !shell)
		return ;
	args = split_cmd(value, " ");
	if (handle_builtin(&args[0], shell))
	{
		return ;
	}
	path = get_path(args[0], getenv("PATH"));
	if (!path)
		perror("Path Error");
	pid = fork();
	if (pid == -1)
		perror("Fork Error");
	else if (pid == 0)
	{
		if (execve(path, args, shell->envp) == -1)
		{
			perror("Execve Error");
			exit (EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, &status, 0);
	free(path);
	ft_free_arrays(args);
}
