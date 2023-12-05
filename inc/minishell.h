/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:37:32 by jbaeza-c          #+#    #+#             */
/*   Updated: 2023/12/05 20:41:13 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

///###   SPLIT_CMD
char	**split_cmd(const char *cmd);

////###   GET_PATH
char	*get_path(char *cmd, const char *env_path);

#endif
