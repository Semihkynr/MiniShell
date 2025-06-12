/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:22:28 by yesoytur          #+#    #+#             */
/*   Updated: 2025/04/15 20:08:41 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	n_len;
	char	*n_s;

	n_len = ft_strlen(s);
	if (!s || start >= n_len)
		return ((char *)ft_calloc(1, sizeof(char)));
	if (start + len > n_len)
		len = n_len - start;
	n_s = (char *)malloc((len + 1) * sizeof(char));
	if (!n_s)
		return (NULL);
	ft_strlcpy(n_s, s + start, len + 1);
	return (n_s);
}
