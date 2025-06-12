/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:20:11 by yesoytur          #+#    #+#             */
/*   Updated: 2025/04/15 20:08:37 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	ft_ltrim(char *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	return (i);
}

static	int	ft_rtrim(char *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1);
	while (i > 0 && ft_strrchr(set, s1[i - 1]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*last_s1;
	int		lindex;
	int		rindex;

	if (!s1 || !set)
		return (NULL);
	lindex = ft_ltrim((char *)s1, set);
	rindex = ft_rtrim((char *)s1, set);
	if (lindex > rindex)
		return (ft_strdup(""));
	last_s1 = (char *)malloc(rindex - lindex + 1 * sizeof(char));
	if (!last_s1)
		return (NULL);
	ft_strlcpy(last_s1, (char *)s1 + lindex, rindex - lindex + 1);
	return (last_s1);
}
