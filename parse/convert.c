/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:59:48 by yesoytur          #+#    #+#             */
/*   Updated: 2025/07/19 21:24:52 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Handles inner loop of convert
t_cmd	*convert_inner(t_token **token)
{
	t_cmd	*new;
	t_cmd	*temp;

	new = init_cmd();
	if (!new)
		return (NULL);
	while (*token && (*token)->type != T_PIPE)
	{
		if ((*token)->type == T_WORD && is_valid_cmd((*token)->value))
			temp = ft_add_cmd(new, *token);
		else if ((*token)->type == T_WORD)
			temp = ft_add_args(new, *token);
		else if ((*token)->type == T_REDIRECT_IN)
			temp = ft_add_infile(new, token);
		else if ((*token)->type == T_REDIRECT_OUT)
			temp = ft_add_outfile(new, token, false);
		else if ((*token)->type == T_APPEND)
			temp = ft_add_outfile(new, token, true);
		else if ((*token)->type == T_HEREDOC)
			temp = ft_add_heredoc(new, token);
		if (!temp)
			return (free_cmd(new), NULL);
		(*token) = (*token)->next;
	}
	return (new);
}

// Converts tokens to cmds
t_cmd	*converter(t_token *token)
{
	t_cmd	*head;
	t_cmd	*new;

	head = NULL;
	while (token)
	{
		new = convert_inner(&token);
		if (!new)
		{
			free_cmd(head); 
			return (NULL);
		}
		if (!head)
			head = new;
		else
			add_cmd(head, new);
		if (token && token->type == T_PIPE)
			token = token->next;
	}
	return (head);
}
