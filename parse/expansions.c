/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:12:53 by yesoytur          #+#    #+#             */
/*   Updated: 2025/08/08 18:39:00 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dollar_expansion(t_shell *shell, int *i, int start)
{
	char	*name;
	char	*value;

	start = *i;
	while (shell->read[*i] && (ft_isalnum(shell->read[*i])
			|| shell->read[*i] == '_'))
		(*i)++;
	name = ft_substr(shell->read, start, *i - start);
	value = find_value(shell->env, name);
	free(name);
	if (!value)
		return (ft_substr(shell->read, start, *i - start));
	return (ft_strdup(value));
}

char	*extract_dollar(t_shell *shell, int *i, int start)
{
	char	c;

	(*i)++;
	if (!shell->read[*i])
		return (ft_strdup("$"));
	c = shell->read[*i];
	if (c == '0')
		return ((*i)++, ft_strdup("bash"));
	if (c == '-')
		return ((*i)++, ft_strdup("himBHs"));
	if (c == '?')
		return ((*i)++, ft_itoa(g_exit_status));
	if (c == '#')
		return ((*i)++, ft_strdup("0"));
	if (!ft_isalnum(c) && c != '_')
		return ((*i)++, ft_strdup(""));
	return (dollar_expansion(shell, i, start));
}

char	*extract_tilde(t_shell *shell, int *i, int start)
{
	char	*path;
	char	*home;

	home = find_value(shell->env, "HOME");
	if (!home)
		home = getenv("HOME");
	(*i)++;
	if (!shell->read[(*i)])
		return (ft_strdup(home));
	else if (shell->read[*i] != '/')
		return (ft_strdup("~"));
	else
	{
		start = (*i);
		while (shell->read[*i])
			(*i)++;
		path = ft_substr(shell->read, start, *i - start);
		return (strjoin_and_free(ft_strdup(home), path));
	}
}
