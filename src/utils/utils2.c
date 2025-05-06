/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:26:23 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/06 18:08:33 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	swap_nodes(t_stack *a, t_stack *b)
{
	char	*tmp_var;
	char	*tmp_value;

	tmp_var = a->var;
	a->var = b->var;
	b->var = tmp_var;
	tmp_value = a->value;
	a->value = b->value;
	b->value = tmp_value;
}

void	sort_env_list(t_stack *head)
{
	t_stack	*current;
	int		sorted;

	if (!head)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		current = head;
		while (current->next)
		{
			if (ft_strcmp(current->var, current->next->var) > 0)
			{
				swap_nodes(current, current->next);
				sorted = 0;
			}
			current = current->next;
		}
	}
}


t_stack **create_stack(t_stack **list , char **enveironment)
{
	char **arr;
	int i;
	
	i = 0;
	while(enveironment[i])
	{
		arr = split_once(enveironment[i] , 0);
		if(arr[1] && arr[1][0] != '\0')
			ft_lstadd_back(list, ft_lstnew(ft_strdup(arr[0]), ft_strdup(arr[1])));
		else
			ft_lstadd_back(list, ft_lstnew(ft_strdup(arr[0]), "")); 
		clear_array(arr);
		i++;
	}
	return(list);
}

char	**split_once(const char *str, int i)
{
	char	**result;
	int		len;

	result = (char **)malloc(sizeof(char *) * 3);
	if (!result)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	result[0] = (char *)malloc(sizeof(char) * (i + 1));
	if (!result[0])
		return (free(result), NULL);
	len = 0;
	while (len < i)
	{
		result[0][len] = str[len];
		len++;
	}
	result[0][len] = '\0';
	if (!str[i])
		result[1] = NULL;
	else
		result[1] = ft_strdup(str + i + 1);
	result[2] = NULL;
	return (result);
}

int	ft_isname(int c)
{
	return (ft_isalnum(c) || c == '_');
}
