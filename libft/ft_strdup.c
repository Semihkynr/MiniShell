/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:25:47 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/04 17:15:43 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*dest;

	size = ft_strlen(s1);
	dest = malloc(size * sizeof(char) + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, size);
	dest[size] = 0;
	return (dest);
}
