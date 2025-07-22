/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:39:38 by yesoytur          #+#    #+#             */
/*   Updated: 2025/07/22 12:43:08 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Parent Process for parsing
t_cmd	*parse(char *input)
{
	t_token	*token_head;
	t_cmd	*cmd_head;

	token_head = tokenizer(input);
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
