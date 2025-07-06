/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:53:04 by skaynar           #+#    #+#             */
/*   Updated: 2025/07/06 12:49:26 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	if(!s1)
		return(999);
	while (s1[i] && s1[i] == s2[i])
		i++;
	
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	clear_array(char **array)
{
	int	i;
	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int ft_n(char *str)
{
	int i;
	i = 2;
	
	if(str[0] != '-' && str[1] != 'n')
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

char    **copy_array(char **array)
{
    int     size;
    size = 0;
    int     i;
    i = 0;
    char    **new_array;

    while (array[size])
        size++;
    new_array = malloc(sizeof(char *) * (size + 1));
    if (!new_array)
        return (NULL);
    while (i < size)
    {
        new_array[i] = ft_strdup(array[i]);
        i++;
    }
    new_array[i] = NULL;
    return (new_array);
}
