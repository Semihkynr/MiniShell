/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:01:25 by yesoytur          #+#    #+#             */
/*   Updated: 2025/04/15 20:09:29 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static t_list	*ft_mapper(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*head;
	void	*n_content;

	head = NULL;
	while (lst)
	{
		n_content = f(lst -> content);
		if (!n_content)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		new_lst = ft_lstnew(n_content);
		if (!new_lst)
		{
			free(n_content);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, new_lst);
		lst = lst -> next;
	}
	return (head);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	head = ft_mapper(lst, f, del);
	return (head);
}
