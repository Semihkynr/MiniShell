/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:03:32 by yesoytur          #+#    #+#             */
/*   Updated: 2025/08/07 22:14:19 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*tokenize_word(t_shell *shell, int *i, bool *quoted)
{
	char	*joined;
	char	*part;

	joined = NULL;
	while (shell->read[*i] && !ft_isspace(shell->read[*i])
		&& !is_operator(shell->read[*i]))
	{
		if (shell->read[*i] == '\'')
			part = extract_single_quote(shell->read, i, 0, quoted);
		else if (shell->read[*i] == '"')
			part = extract_double_quote(shell, i, 0, quoted);
		else if (shell->read[*i] == '$')
		{
			part = extract_dollar(shell, i, 0);
			g_exit_status = 0;
		}
		else if (!joined && shell->read[*i] == '~')
			part = extract_tilde(shell, i, 0);
		else
			part = extract_word(shell->read, i, 0);
		if (!part)
			return (free(joined), NULL);
		joined = strjoin_and_free(joined, part);
	}
	return (assign_token(joined, quoted));
}

t_token	*tokenize_operator(char *input, int *i)
{
	int		start;
	char	*op;
	bool	quoted;

	quoted = false;
	start = *i;
	while (input[*i] && is_operator(input[*i]) && !ft_isspace(input[*i]))
		(*i)++;
	op = ft_substr(input, start, *i - start);
	if (!op)
		return (NULL);
	return (assign_token(op, &quoted));
}

t_token	*tokenizer(t_shell *shell)
{
	int		i;
	t_token	*head;
	t_token	*new;

	head = NULL;
	i = 0;
	while (shell->read[i])
	{
		skip_spaces(shell->read, &i);
		if (!shell->read[i])
			break ;
		new = extract_token(shell, &i);
		if (!new)
		{
			free_token(head);
			return (NULL);
		}
		if (!head)
			head = new;
		else
			add_token(head, new);
	}
	return (head);
}
