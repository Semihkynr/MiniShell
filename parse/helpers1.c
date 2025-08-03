/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:57:15 by yesoytur          #+#    #+#             */
/*   Updated: 2025/08/03 19:56:24 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_double(char **args)
{
	char	**current;

	if (!args)
		return ;
	current = args;
	while (*current)
		free(*current++);
	free(args);
}

// Custom file error printer
void	print_file_error(char *file_name)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file_name);
}

// Custom syntax error printer
void	print_syntax_error(char *token, int mod)
{
	if (mod == 0)
		ft_putstr_fd("minishell: syntax error unclosed single quote\n", 2);
	else if (mod == 1)
		ft_putstr_fd("minishell: syntax error unclosed double quote\n", 2);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("'\n", 2);	
	}
}
