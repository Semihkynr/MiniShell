/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:22:02 by yesoytur          #+#    #+#             */
/*   Updated: 2025/07/08 23:57:36 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Skips spaces until none space character
void	skip_spaces(const char *input, int *i)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
}

// Skips until one of the characters in `delims` is found
void	skip_until_chars(char *input, int *i, const char *delims)
{
	while (input[*i] && !ft_strchr(delims, input[*i]))
		(*i)++;
}

// Stops when encountering a quote, $, space, or operator
static int	is_stop_char(char c)
{
	return (c == '\'' || c == '"' || c == '$'
		|| ft_isspace(c) || is_operator(c));
}

// Skips until !is_stop_char
void	skip_until_specials(char *input, int *i)
{
	while (input[*i] && !is_stop_char(input[*i]))
		(*i)++;
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}
