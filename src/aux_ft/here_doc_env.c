/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:53:25 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/22 14:47:56 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*doc_switch(t_minishell *shell, char *src, int cnt, int i)
{
	int		j;
	char	*value;

	j = -1;
	value = NULL;
	while (shell->envp[++j])
	{
		if (!ft_strncmp(&src[i + 1], shell->envp[j], cnt - i - 1))
		{
			value = ft_calloc(1, ft_strlen(src)
				+ ft_strlen(shell->envp[j]) - 2 * (cnt - i) + 1);
			ft_strncpy(value, src, i);
			ft_strncpy(value, &(shell->envp[j][cnt-i]),
				ft_strlen(&(shell->envp[j][cnt-i])));
			ft_strncpy(value, &src[cnt], ft_strlen(&src[cnt]));
			break;
		}
	}
	return (value);
}

char	*exit_switch(t_minishell *shell, char *src, int cnt, int i)
{
	char	*value;
	char	*exit;

	value = NULL;
	exit = ft_itoa(shell->last_exit_status);
	value = ft_calloc(1, ft_strlen(src) + ft_strlen(exit) - 2 * (cnt - i));
	ft_strncpy(value, src, i);
	ft_strncpy(value, exit, ft_strlen(exit));
	ft_strncpy(value, &src[cnt + 1], ft_strlen(&src[cnt + 1]));
	free(exit);
	return (value);
}

char	*empty_switch(t_minishell *shell, char *src, int cnt, int i)
{
	char	*value;

	(void)shell;
	value = NULL;
	value = ft_calloc(1, ft_strlen(src) - (cnt - i));
	ft_strncpy(value, src, i);
	ft_strncpy(value, "", 0);
	ft_strncpy(value, &src[cnt], ft_strlen(&src[cnt]));
	return (value);
}

char	*doc_envp(t_minishell *shell, char *src)
{
	char	*line;
	int		cnt;
	int		i;

	i = 0;
	line = NULL;
	while (src[i] != '$')
		i++;
	cnt = i + 1;
	if (!src[i])
		return (NULL);
	if (src[cnt] == '$')
		line = ft_strdup(src);
	if (src[cnt] == '?')
		line = exit_switch(shell, src, cnt, i);
	while (src[cnt] && src[cnt] != ' ' && src[cnt] != 39
		&& src[cnt] != 34 && src[cnt] != '\n')
		cnt++;
	if (!line)
		line = doc_switch(shell, src, cnt, i);
	if (!line)
		line = empty_switch(shell, src, cnt, i);
	free(src);
	return (line);
}
