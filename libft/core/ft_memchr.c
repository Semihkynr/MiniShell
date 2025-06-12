/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:30 by yesoytur          #+#    #+#             */
/*   Updated: 2025/04/15 20:07:11 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*n_s;

	n_s = (const unsigned char *)s;
	while (n--)
	{
		if (*n_s == (unsigned char)c)
			return ((void *)n_s);
		n_s++;
	}
	return (NULL);
}
