/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:13:42 by yesoytur          #+#    #+#             */
/*   Updated: 2025/07/07 18:13:28 by skaynar          ###   ########.fr       */
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
