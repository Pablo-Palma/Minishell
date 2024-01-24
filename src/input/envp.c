/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:00:47 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/23 15:09:21 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_switch(t_minishell *shell, t_token *token, int i, int cnt)
{
	int		j;
	char	*value;

	j = -1;
	value = NULL;
	while (shell->envp[++j])
	{
		if (!ft_strncmp(&token->value[i + 1], shell->envp[j], cnt - i - 1))
		{
			value = ft_calloc(1, ft_strlen(token->value)
					+ ft_strlen(shell->envp[j]) - 2 * (cnt - i) + 1);
			ft_strncpy(value, token->value, i);
			ft_strncpy(value, &(shell->envp[j][cnt - i]),
				ft_strlen(&(shell->envp[j][cnt - i])));
			ft_strncpy(value, &token->value[cnt],
				ft_strlen(&token->value[cnt]));
			free(token->value);
			token->value = value;
			return (value);
		}
	}
	return (value);
}

void	switch_envp(t_minishell *shell, t_token *token, int i)
{
	char	*new_value;
	int		cnt;

	cnt = i + 1;
	if (token->type == AST_HEREDOC_DELIM)
		return ;
	while (token->value[cnt] && token->value[cnt] != ' '
		&& token->value[cnt] != '\'')
		cnt++;
	if (!token->value[1] || token->value[1] == '?' || token->value[1] == '$')
		return ;
	new_value = ft_switch(shell, token, i, cnt);
	if (!new_value)
	{
		new_value = ft_calloc(1, ft_strlen(token->value) - (cnt - i) + 1);
		ft_strncpy(new_value, token->value, i);
		ft_strncpy(new_value, "", 0);
		ft_strncpy(new_value, &token->value[cnt],
			ft_strlen(&token->value[cnt]));
		free(token->value);
		token->value = new_value;
	}
}

void	handle_envp(t_minishell *shell, t_token *node)
{
	t_token	*token;
	int		i;

	token = node;
	while (token)
	{
		if (token->envvar)
		{
			i = 0;
			while (strchr(token->value, '$'))
			{
				while (token->value[i] != '$')
					i++;
				if (token->value[i + 1] == '$' || token->value[i + 1] == '?')
					token->value = ft_double(shell, token->value, i, i + 2);
				else
					switch_envp(shell, token, i);
			}
		}
		token = token->next;
	}
}
