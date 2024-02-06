/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:00:47 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/02/06 16:49:25 by jbaeza-c         ###   ########.fr       */
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
			return (value);
		}
	}
	return (value);
}

void	switch_envp(t_minishell *shell, t_token *token, int *i, int *quote)
{
	char	*new_value;
	int		cnt;

	cnt = *i + 1;
	new_value = NULL;
	if (token->type == AST_HEREDOC_DELIM)
		return ;
	if (!token->value[cnt] || ft_isspace(token->value[cnt]))
		new_value = empty_env_switch(shell, token->value, *i, cnt);
	if (!token->value[1] || token->value[1] == '?' || token->value[1] == '$')
		return ;
	while (ft_isalpha(token->value[cnt]) || ft_isdigit(token->value[cnt]))
		cnt++;
	if (!new_value)
		new_value = ft_switch(shell, token, *i, cnt);
	if (!new_value)
		new_value = empty_env_switch(shell, token->value, *i, cnt);
	free(token->value);
	token->value = new_value;
	*i = -1;
	*quote = 0;
}

void	echo_double(t_minishell *shell, t_token *token, int *i, int *quote)
{
	char	*aux;

	aux = token->value;
	token->value = ft_double(shell, token->value, *i);
	*i = -1;
	*quote = 0;
	free(aux);
}

void	handle_envp(t_minishell *shell, t_token *node)
{
	t_token	*token;
	int		quote;
	int		i;

	token = node;
	while (token)
	{
		quote = 0;
		i = -1;
		while (token->type != AST_FILE && token->value[++i])
		{
			if (!quote && (token->value[i] == '\'' || token->value[i] == '\"'))
				quote = token->value[i];
			else if (token->value[i] == quote)
				quote = 0;
			if (quote != '\'' && token->value[i] == '$')
			{
				if (token->value[i + 1] == '$' || token->value[i + 1] == '?')
					echo_double(shell, token, &i, &quote);
				else
					switch_envp(shell, token, &i, &quote);
			}
		}
		token = token->next;
	}
}
