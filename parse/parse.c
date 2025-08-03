/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:39:38 by yesoytur          #+#    #+#             */
/*   Updated: 2025/08/03 20:01:45 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Parent Process for parsing
t_cmd	*parse(t_shell *shell)
{
	t_token	*token_head;
	t_cmd	*cmd_head;

	token_head = tokenizer(shell);
	if (!token_head)
		return (NULL);
	if (!lexer(token_head))
	{
		free_token(token_head);
		return (NULL);
	}
	cmd_head = converter(token_head);
	free_token(token_head);
	if (!cmd_head)
		return (NULL);
	return (cmd_head);
}
