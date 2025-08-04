/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:05:25 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/04 15:59:27 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_node(t_stack **head, t_stack *prev, t_stack *target)
{
	if (prev)
		prev->next = target->next;
	else
		*head = target->next;
	free(target->var);
	if (target->value)
		free(target->value);
	free(target);
}

static void	find_unset(t_stack **env, char *str)
{
	t_stack	*fake;
	t_stack	*prev;

	if (!env || !*env)
		return ;
	fake = *env;
	prev = NULL;
	while (fake)
	{
		if (ft_strcmp(fake->var, str) == 0)
		{
			delete_node(env, prev, fake);
			return ;
		}
		prev = fake;
		fake = fake->next;
	}
}

void	cmd_unset(t_stack **env, t_stack **env_exp, char **temp)
{
	int	i;

	i = 1;
	while (temp[i])
	{
		find_unset(env, temp[i]);
		find_unset(env_exp, temp[i]);
		i++;
	}
}
