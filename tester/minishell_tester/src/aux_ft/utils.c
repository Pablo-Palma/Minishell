/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:46:20 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/08 11:20:48 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(const char *msg, int use_perror, int error_code)
{
	if (use_perror)
		perror(msg);
	else
		ft_printf("%s\n", msg);
	exit(error_code);
}

void	free_shell(t_minishell *shell)
{
	if (shell->input_line)
		free(shell->input_line);
	if (shell->envp)
		free_env(&(shell->envp));
	free_ast(shell->ast);
}

void	copy_envp(t_minishell *shell, char **envp)
{
	int		i;
	int		envp_len;
	char	**new_envp;

	i = 0;
	envp_len = 0;
	while (envp[envp_len])
		envp_len++;
	new_envp = (char **)malloc(sizeof(char *) * (envp_len + 1));
	if (!new_envp)
		return ;
	while (i < envp_len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[envp_len] = NULL;
	shell->envp = new_envp;
	shell->og_envp = new_envp;
}

void	init_minishell(t_minishell *shell, char **envp)
{
	if (!shell)
		return ;
	copy_envp(shell, envp);
	shell->fd_read = 0;
	shell->fd_write = 1;
	shell->input_redirect = 0;
	shell->output_redirect = 0;
	shell->input_line = NULL;
	shell->ast = NULL;
	shell->pipe_list = NULL;
	shell->last_cmd = 0;
	shell->hd_pipes = 0;
	shell->hd_pipes_read = 0;
	shell->last_exit_status = 0;
	shell->shell_pid = 0;
}

void	reset_minishell(t_minishell *shell)
{
	if (shell->fd_read != 0)
		close(shell->fd_read);
	shell->fd_read = 0;
	shell->fd_write = 1;
	shell->input_redirect = 0;
	shell->output_redirect = 0;
}
