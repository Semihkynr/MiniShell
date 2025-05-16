/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstfnc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:51:24 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/10 15:02:52 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_stack	*ft_lstnew(char *var, char *value)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (0);
	node->var = var;
	if (value && value[0])
	{
		node->equals = '=';
		node->nail = '"';
		node->value = value;
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

t_stack	*ft_lstlast(t_stack *lst)
{
	t_stack	*temp;

	temp = lst;
	if (!temp)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*end;

	if (!*lst)
		*lst = new;
	else
	{
		end = ft_lstlast(*lst);
		end->next = new;
	}
}

int	ft_lstsize(t_stack *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_lstclear(t_stack **lst)
{
	t_stack	*temp;

	if (lst == NULL || *lst == NULL)
	{
		free(lst);
		return ;
	}
	temp = *lst;
	while (*lst)
	{
		*lst = temp->next;
        free(temp->var);
        free(temp->value);
		free(temp);
		temp = *lst;
	}
	free(lst);
}
