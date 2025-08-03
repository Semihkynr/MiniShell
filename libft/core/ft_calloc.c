/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:48:34 by yesoytur          #+#    #+#             */
/*   Updated: 2025/08/03 20:12:02 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*n;

	n = (void *)malloc(count * size);
	if (!n)
		return (NULL);
	ft_bzero(n, count * size);
	return (n);
}
