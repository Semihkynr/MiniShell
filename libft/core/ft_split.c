/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:09:41 by yesoytur          #+#    #+#             */
/*   Updated: 2025/04/15 20:07:50 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	*ft_free(char **s, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static	char	**ft_main_maloc(char const *s, char c)
{
	size_t	i;
	size_t	counter;
	char	**d_s;

	i = 0;
	counter = 0;
	if (s[0] != c)
		counter++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			counter++;
		i++;
	}
	d_s = (char **)malloc((counter + 1) * sizeof(char *));
	if (!d_s)
		return (NULL);
	d_s[counter] = NULL;
	return (d_s);
}

static	char	**ft_side_maloc(char const *s, char c, char **d_s)
{
	size_t	i;
	size_t	j;
	size_t	counter;

	i = 0;
	j = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			counter++;
			if (s[i + 1] == c || !s[i + 1])
			{
				d_s[j] = (char *)malloc((counter + 1) * sizeof(char));
				if (!d_s[j])
					return (ft_free(d_s, j));
				counter = 0;
				j++;
			}
		}
		i++;
	}
	return (d_s);
}

static	char	**ft_cpy_maloc(char const *s, char c, char **d_s)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			d_s[j][k] = s[i];
			i++;
			k++;
			if (s[i] == c || s[i] == '\0')
			{
				d_s[j][k] = '\0';
				k = 0;
				j++;
			}
		}
	}
	return (d_s);
}

char	**ft_split(char const *s, char c)
{
	char	**d_s;

	if (!s)
		return (NULL);
	if (!s[0])
	{
		d_s = malloc(sizeof(char *));
		if (!d_s)
			return (NULL);
		d_s[0] = NULL;
		return (d_s);
	}
	d_s = ft_main_maloc(s, c);
	if (!d_s)
		return (NULL);
	d_s = ft_side_maloc(s, c, d_s);
	if (!d_s)
		return (NULL);
	d_s = ft_cpy_maloc(s, c, d_s);
	if (!d_s)
		return (NULL);
	return (d_s);
}
