/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:53:04 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/02 17:46:57 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	clear_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int ft_n(char *str , char *n)
{
	int i;
	i = 2;
	if(n[0] != '-' && n[1] != 'n')
		return(1);
	while(str[i])
	{
		if(str[i] == 'n')
			i++;
		else
			return(1);
	}
	return(0);
}

int sizeof_array(char **av)
{
	int i;
	
	i = 0;
	while(av[i])
		i++;
	return(i);
}