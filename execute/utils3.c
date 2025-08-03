/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:23:05 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/03 18:32:54 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_value(t_stack **stack, char *name)
{
    t_stack *fake;
    
    fake = *stack;
	while (fake)
	{
		if (fake->var && name && ft_strcmp(fake->var, name) == 0)
			return (fake->value);
		fake = fake->next;
	}
	return (NULL);
}