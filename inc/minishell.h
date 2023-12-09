/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:54:15 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/09 12:17:35 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_PATH 260 //As a convention

# include "libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

extern volatile sig_atomic_t sigint_recived;

typedef struct	s_minishell
{
	char	**envp;
	int		fd_in;
	int		fd_out;
	char	*input_line;
	char	**commands;
	int		number_commands;
}	t_minishell;

///###   SPLIT_CMD
char    **split_cmd(const char *cmd, const char *delimiters);

////###   GET_PATH
char	*get_path(char *cmd, const char *env_path);

///###   EXECUTE
void	execute_command(char *input, t_minishell *shell);

///###	MINISHELL
int		minishell(char **envp);

///###   SIGNAL
void	setup_signal_handlers();

///###   BUILTIN
int		handle_builtin(char **cmd_args, t_minishell *shell);
void	echo_command(char **cmd_args);
void	cd_command(char **cmd_args);
void	pwd_command(void);
int		export_command(char **cmd_args, t_minishell *shell);
int		unset_command(char **args, t_minishell *shell);
void	env_command(t_minishell *shell);
int		exit_command(char **cmd_args, t_minishell *shell);

///###	PIPE
int	execute_non_pipe_command(t_minishell *shell);
int	execute_pipe_command(t_minishell *shell);

///###	INPUT
int	handle_input(char *input, t_minishell *shell);
int	ft_tablen(char **tab);

#endif
