/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:12:53 by yesoytur          #+#    #+#             */
/*   Updated: 2025/07/20 14:32:01 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Extract dollars inner part 
char	*dollar_expansion(char *input, int *i, int start)
{
	char	*name;
	char	*value;

	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	name = ft_substr(input, start, *i - start);
	value = getenv(name);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

// Extract dollar expansions
char	*extract_dollar(char *input, int *i, int start)
{
	char	c;

	(*i)++;
	if (!input[*i])
		return (ft_strdup("$"));
	c = input[*i];
	if (c == '0')
		return ((*i)++, ft_strdup("bash"));
	if (c == '-')
		return ((*i)++, ft_strdup("himBH"));
	if (c == '?')
		return ((*i)++, ft_itoa(g_exit_status));
	if (c == '#')
		return ((*i)++, ft_strdup("0"));
	if (!ft_isalnum(c) && c != '_')
		return ((*i)++, ft_strdup(""));
	return (dollar_expansion(input, i, start));
}

// Extract tilde expansions
char	*extract_tilde(char *input, int *i, int start)
{
	char	*path;
	char	*home;
	
	home = getenv("HOME");
	if (!home)
		return (ft_strdup("~"));
	(*i)++;
	if (!input[(*i)]) // ~
		return (ft_strdup(home));
	else if (input[*i] != '/') // ~somegibberish
		return (ft_strdup("~"));
	else // ~/somegibberish
	{
		start = (*i);
		while (input[*i])
			(*i)++;
		path = ft_substr(input, start, *i - start);
		return (strjoin_and_free(ft_strdup(home), path));
	}
}
