/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:39:38 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/20 15:46:59 by yesoytur         ###   ########.fr       */
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
	{
		printf("tokenize error: failed to tokenize input\n");
		return (NULL);
	}
	if (!lexer(token_head))
	{
		printf("lex error: failed to lex tokens\n");
		free_token(token_head);
		return (NULL);
	}
	print_tokens(token_head); //
	cmd_head = converter(token_head);
	free_token(token_head);
	if (!cmd_head)
	{
		printf("convert error: failed to convert tokens\n");
		return (NULL);
	}
	return (cmd_head);
}
