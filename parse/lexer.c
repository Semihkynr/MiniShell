/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:03:40 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/10 19:47:52 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Gets tokens type based on the value
static t_token_type	get_token_type(const char *str)
{
	if (ft_iseq(str, "|") && ft_strlen(str) == 1)
		return (T_PIPE);
	else if (ft_iseq(str, "<<") && ft_strlen(str) == 2)
		return (T_HEREDOC);
	else if (ft_iseq(str, ">>") && ft_strlen(str) == 2)
		return (T_APPEND);
	else if (ft_iseq(str, "<") && ft_strlen(str) == 1)
		return (T_REDIRECT_IN);
	else if (ft_iseq(str, ">") && ft_strlen(str) == 1)
		return (T_REDIRECT_OUT);
	else if (is_valid_word_token(str))
		return (T_WORD);
	else
		return (T_UNKNOWN);
}

// Lexes all tokens (assigns their type)
int	lexer(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->quoted)
			temp->type = T_WORD;
		else
			temp->type = get_token_type(temp->value);
		if (temp->type == T_UNKNOWN)
		{
			printf("syntax error near unexpected token `%s`\n", temp->value);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}
