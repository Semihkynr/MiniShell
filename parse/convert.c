/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:59:48 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/19 22:31:23 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Handles inner loop of convert
t_cmd	*convert_inner(t_token **token)
{
	t_cmd	*new;

	new = init_cmd();
	if (!new)
		return (NULL);
	while (*token && (*token)->type != T_PIPE)
	{
		if ((*token)->type == T_WORD && is_valid_cmd((*token)->value))
			new = ft_add_cmd(new, *token);
		else if ((*token)->type == T_WORD)
			new = ft_add_args(new, *token);
		else if ((*token)->type == T_REDIRECT_IN)
			new = ft_add_infile(new, token);
		else if ((*token)->type == T_REDIRECT_OUT)
			new = ft_add_outfile(new, token, false);
		else if ((*token)->type == T_APPEND)
			new = ft_add_outfile(new, token, true);
		else if ((*token)->type == T_HEREDOC)
			new = ft_add_heredoc(new, token);
		if (!new)
			return (NULL);
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
