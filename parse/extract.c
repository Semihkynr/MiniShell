/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:23:24 by yesoytur          #+#    #+#             */
/*   Updated: 2025/07/22 12:41:20 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Extracts  single quoted strings, supports adjacent segments
char	*extract_single_quote(char *input, int *i, int start, bool *quoted)
{
	char	*joined;
	char	*part;

	joined = NULL;
	*quoted = true;
	while (input[*i] == '\'')
	{
		(*i)++;
		start = *i;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		// Check if quote was closed
		if (input[*i] != '\'')
		{
			print_syntax_error("single quote", 0);
			free(joined);
			return (NULL);
		}
		part = ft_substr(input, start, (*i) - start);
		joined = strjoin_and_free(joined, part);
		(*i)++;
	}
	return (joined);
}

// extract_double_quote helper function
char	*extract_double_inner(char *input, int *i, int start)
{
	char	*joined;
	char	*part;

	joined = NULL;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
			part = extract_dollar(input, i, 0);
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

// Extracts  double quoted strings, supports adjacent segments and expansion
char	*extract_double_quote(char *input, int *i, int start, bool *quoted)
{
	char	*joined;
	char	*part;

	joined = NULL;
	*quoted = true;
	while (input[*i] == '"')
	{
		(*i)++;
		part = extract_double_inner(input, i, start);
		joined = strjoin_and_free(joined, part);
		if (input[*i] == '"')
			(*i)++;
		else
		{
			print_syntax_error("double quote", 1);
			free(joined);
			return (NULL);
		}
	}
	return (joined);
}

// Extracts word
char	*extract_word(char *input, int *i, int start)
{
	start = *i;
	skip_until_specials(input, i);
	return (ft_substr(input, start, *i - start));
}

// Extracts token
t_token	*extract_token(char *input, int *i)
{
	bool	quoted;

	quoted = false;
	if (is_operator(input[*i]))
		return (tokenize_operator(input, i));
	return (tokenize_word(input, i, &quoted));
}
