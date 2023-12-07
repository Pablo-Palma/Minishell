/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:54:15 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/07 03:02:25 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_minishell
{
	char	**envp;
	int		fd_in;
	int		fd_out;
	char	*input_line;
	char	**commands;
	int		number_commands;
}	t_minishell;

///###   SPLIT_CMD
char	**split_cmd(const char *cmd);

////###   GET_PATH
char	*get_path(char *cmd, const char *env_path);

///###   EXECUTE
void	execute_command(char *input, t_minishell *shell);

///###	MINISHELL
int		minishell(char **envp);

///###	INPUT HANDLING
int		handle_input(char *input, t_minishell *shell);

int		execute_pipe_command(t_minishell *shell);

#endif
