/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:04:44 by yesoytur          #+#    #+#             */
/*   Updated: 2025/04/15 20:07:18 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*n_dst;
	const unsigned char	*n_src;

	if (!dst && !src)
		return (NULL);
	n_dst = (unsigned char *)dst;
	n_src = (const unsigned char *)src;
	while (n--)
		*n_dst++ = *n_src++;
	return (dst);
}
