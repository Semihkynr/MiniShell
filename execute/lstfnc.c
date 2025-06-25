/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstfnc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:51:24 by skaynar           #+#    #+#             */
/*   Updated: 2025/06/24 18:57:58 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_stack	*sk_lstnew(char *var, char *value)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (0);
	node->var = var;
	if (value)
	{
		node->equals = '=';
		node->nail = '"';
		if (value[0])
			node->value = value;
		else
			node->value = ft_strdup("");
	}
	else
	{
		node->equals = 0;
		node->nail = 0;
		node->value = ft_strdup("");
	}
	node->next = NULL;
	return (node);
}

t_stack	*sk_lstlast(t_stack *lst)
{
	if (!lst)
		return (NULL);
	while (lst && (lst -> next))
		lst = lst -> next;
	return (lst);
}

void	sk_lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = sk_lstlast(*lst);
	last -> next = new;
}

void	sk_lstclear(t_stack **lst)
{
	t_stack	*temp;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = temp->next;
		free(temp->var);
		free(temp->value);
		free(temp);
	}
	*lst = NULL;
}
int	sk_lstsize(t_cmd *lst)
{
	int	counter;
	counter = 0;
	while (lst)
	{
		lst = lst -> next;
		counter++;
	}
	return (counter);
}

