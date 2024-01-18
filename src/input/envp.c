/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaeza-c <jbaeza-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:00:47 by jbaeza-c          #+#    #+#             */
/*   Updated: 2024/01/18 14:24:20 by jbaeza-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	switch_envp(t_minishell *shell, char **tab, int i)
{
	int	j;
	int	k;

	j = 0;
	if (!tab[i][1])
		return ;
	if (ft_strncmp(tab[i], "$?", 2) == 0)
		return ;
	while (shell->envp[j])
	{
		if (!ft_strncmp(&tab[i][1], shell->envp[j], ft_strlen(tab[i]) - 1))
		{
			free(tab[i]);
			k = 0;
			while (shell->envp[j][k] != '=')
				k++;
			k++;
			tab[i] = ft_strdup(&(shell->envp[j][k]));
			return ;
		}
		j++;
	}
	free(tab[i]);
	tab[i] = ft_strdup("");
}*/

void	switch_envp(t_minishell *shell, t_token *token, int i)
{
	char	*new_value;
	int		cnt;
	int		j;

	cnt = i + 1;
	j = 0;
	if ((token->value[i]  == '$' && token->value[i + 1] == '?')
		|| token->type == AST_HEREDOC_DELIM)
		return ;
	while (token->value[cnt] && token->value[cnt] != ' ' && token->value[cnt] != '\'')
		cnt++;
	if (!token->value[1] || token->value[1] == '?')
		return ;
	while (shell->envp[++j])
	{
		if (!ft_strncmp(&token->value[i + 1], shell->envp[j], cnt - i - 1))
		{
			new_value = ft_calloc(1, ft_strlen(token->value) + ft_strlen(shell->envp[j]) - 2 * (cnt - i));
			ft_strncpy(new_value, token->value, i);
			ft_strncpy(new_value, &(shell->envp[j][cnt-i]), ft_strlen(&(shell->envp[j][cnt-i])));
			ft_strncpy(new_value, &token->value[cnt], ft_strlen(&token->value[cnt]));
			free(token->value);
			token->value = new_value;
			return ;
		}
	}
	new_value = ft_calloc(1, ft_strlen(token->value) - (cnt - i));
	ft_strncpy(new_value, token->value, i);
	ft_strncpy(new_value, "", 0);
	ft_strncpy(new_value, &token->value[cnt], ft_strlen(&token->value[cnt]));
	free(token->value);
	token->value = new_value;
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
			i = -1;
			while (token->value[++i])
				if (token->value[i] == '$')
					switch_envp(shell, token, i);
		}
		token = token->next;
	}
}
