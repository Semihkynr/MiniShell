/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:13:11 by yesoytur          #+#    #+#             */
/*   Updated: 2025/04/15 20:11:01 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	chr;

	chr = (unsigned char)c;
	if (!s)
		return (NULL);
	while (1)
	{
		if (*s == chr)
			return ((char *)s);
		if (!(*s))
			break ;
		s++;
	}
	return (NULL);
}
