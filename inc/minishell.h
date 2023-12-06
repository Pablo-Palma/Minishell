/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:54:15 by pabpalma          #+#    #+#             */
/*   Updated: 2023/12/06 12:21:41 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_minishell
{
	char	**envp;
	int		fd_in;
	int		fd_out;
	char	*input_line;
	char	**commands;
}	t_minishell;

///###   SPLIT_CMD
char	**split_cmd(const char *cmd);

////###   GET_PATH
char	*get_path(char *cmd, const char *env_path);

///###   EXECUTE
void	execute_command(char *input, t_minishell *shell);

///###	MINISHELL
int		minishell(char **envp);

#endif
