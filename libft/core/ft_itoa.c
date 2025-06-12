/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yesoytur <yesoytur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:52:47 by yesoytur          #+#    #+#             */
/*   Updated: 2025/04/15 20:07:07 by yesoytur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	size_t	int_len(int n)
{
	size_t	len;

	len = 0;
	while (n / 10)
	{
		n /= 10;
		len++;
	}
	return (len + 1);
}

static	char	*ft_neg_itoa(unsigned int n, char *a, size_t len)
{
	char	temp;
	size_t	i;
	size_t	j;

	n = 4294967296 - n;
	a[len - 1] = '-';
	a[0] = '\0';
	i = 1;
	while (i < len - 1)
	{
		a[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	j = 0;
	while (i > j)
	{
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
		i--;
		j++;
	}
	return (a);
}

static	char	*ft_pos_itoa(int n, char *a, size_t len)
{
	size_t	i;
	size_t	j;
	char	temp;

	a[0] = '\0';
	i = 1;
	while (i < len)
	{
		a[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	i--;
	j = 0;
	while (i > j)
	{
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
		i--;
		j++;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	char	*a;
	size_t	len;

	if (n >= 0)
	{
		len = int_len(n) + 1;
		a = (char *)malloc((len) * sizeof(char));
		if (!a)
			return (NULL);
		a = ft_pos_itoa(n, a, len);
	}
	else
	{
		len = int_len(n) + 2;
		a = (char *)malloc((len) * sizeof(char));
		if (!a)
			return (NULL);
		a = ft_neg_itoa(n, a, len);
	}
	return (a);
}
