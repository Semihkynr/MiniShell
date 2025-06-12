/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:04:02 by yesoytur          #+#    #+#             */
/*   Updated: 2025/05/31 19:57:13 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks if space
int	ft_isspace(char c)
{
	return ((c == ' ') || (c >= '\t' && c <= '\r'));
}

// Checks if operator
int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

// Checks if is equal
int	ft_iseq(const char *a, const char *b)
{
	return (ft_strncmp(a, b, ft_strlen(b) + 1) == 0);
}

// Checks if is valid word token
int	is_valid_word_token(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isprint(str[i]))
			return (0);
		if (ft_isspace(str[i]) || is_operator(str[i]) || str[i] == ';')
			return (0);
		i++;
	}
	return (1);
}

// Checks if is valid cmd
int	is_valid_cmd(const char *cmd)
{
	int			i;
	const char	*builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
	};

	if (!cmd)
		return (0);
	i = 0;
	while (builtins[i])
	{
		if (ft_iseq(cmd, builtins[i]))
			return (1);
		i++;
	}
	return (0);
}
