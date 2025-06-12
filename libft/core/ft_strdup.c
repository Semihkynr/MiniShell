/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:13:42 by yesoytur          #+#    #+#             */
/*   Updated: 2025/04/15 20:07:57 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*cpy_s1;

	len = ft_strlen(s1);
	cpy_s1 = (char *)malloc((len + 1) * sizeof(char));
	if (!cpy_s1)
		return (NULL);
	ft_strlcpy(cpy_s1, s1, len + 1);
	return (cpy_s1);
}
