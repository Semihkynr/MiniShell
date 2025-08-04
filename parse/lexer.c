/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:03:40 by yesoytur          #+#    #+#             */
/*   Updated: 2025/08/04 16:14:23 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	last_error_message(t_token *curr)
{
	if (curr->type == T_PIPE)
		print_syntax_error("|", 2);
	else if (curr->type == T_HEREDOC)
		print_syntax_error("<<", 2);
	else
		print_syntax_error("newline", 2);
}

static int	type_order_check(t_token *head)
{
	t_token	*curr;

	if (!head)
		return (1);
	if (head->type != T_WORD && head->type != T_HEREDOC)
	{
		print_syntax_error(head->value, 2);
		return (0);
	}
	curr = head;
	while (curr && curr->next)
	{
		if (curr->type != T_WORD && curr->next->type != T_WORD)
		{
			print_syntax_error(curr->next->value, 2);
			return (0);
		}
		curr = curr->next;
	}
	if (curr && curr->type != T_WORD)
	{
		last_error_message(curr);
		return (0);
	}
	return (1);
}

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
			print_syntax_error(temp->value, 2);
			return (0);
		}
		temp = temp->next;
	}
	if (!type_order_check(tokens))
		return (0);
	return (1);
}
