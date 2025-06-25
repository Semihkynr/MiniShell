/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:57:15 by yesoytur          #+#    #+#             */
/*   Updated: 2025/06/20 13:44:48 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_double(char **args)
{
	char	**current;

	if (!args)
		return ;
	current = args;
	while (*current)
		free(*current++);
	free(args);
}
