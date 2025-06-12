/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:57:15 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/17 21:27:07 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// extract_double_quote helper function
char	*extract_double_inner(char *input, int *i, int start)
{
	char	*joined;
	char	*part;

	joined = NULL;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
			part = extract_expansion(input, i, 0);
		else
		{
			start = *i;
			skip_until_chars(input, i, "\"$");
			part = ft_substr(input, start, (*i) - start);
		}
		joined = strjoin_and_free(joined, part);
	}
	return (joined);
}

void	free_double(char **args)
{
	char	**current;

	if (!args)
		return ;
	current = args;
	while (*current)
		free(*current++);
	free(args);
}
