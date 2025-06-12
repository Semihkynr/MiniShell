/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:05:52 by yesoytur          #+#    #+#             */
/*   Updated: 2025/04/15 20:07:21 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*n_dest;
	const unsigned char	*n_src;

	n_dest = (unsigned char *)dst;
	n_src = (const unsigned char *)src;
	if (n_dest == n_src || !len)
		return (dst);
	if (n_dest < n_src)
		return (ft_memcpy(dst, src, len));
	while (len--)
		n_dest[len] = n_src[len];
	return (dst);
}
