/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:40:24 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/19 22:17:35 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Initializes token
t_token	*init_token(void)
{
	t_token	*head;

	head = ft_calloc(1 ,sizeof(t_token));
	if (!head)
	{
		printf("Token can not be initialized\n");
		return (NULL);
	}
	return (head);
}

// Frees token/tokens
void	free_token(t_token *head)
{
	t_token *temp;
	t_token *next;

	temp = head;
	while (temp)
	{
		next = temp->next;
		if (temp->value)
			free(temp->value);
		free(temp);
		temp = next;
	}
}

// Adds token back
void	add_token(t_token *head, t_token *new)
{
	t_token	*prev;

	if (!head || !new)
		return ;
	prev = head;
	while (prev->next)
		prev = prev->next;
	prev->next = new;
}

// Initializes and assigns token
t_token	*assign_token(char *value, bool *quoted)
{
	t_token	*new;

	new = init_token();
	if (!new)
		return (NULL);
	if (!value)
	{
		free(new);
		return (NULL);
	}
	new->value = value;
	new->quoted = (*quoted);
	return (new);
}

// Prints tokens for debugging
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("TOKEN: %-10s  TYPE: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}
