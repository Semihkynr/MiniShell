/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:23:05 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/07 22:09:31 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_value(t_stack **stack, char *name)
{
	t_stack	*fake;

	fake = *stack;
	while (fake)
	{
		if (fake->var && name && ft_strcmp(fake->var, name) == 0)
			return (fake->value);
		fake = fake->next;
	}
	return (NULL);
}

int	ft_open(char *file, int val, bool i)
{
	int	rtn;

	if (val)
	{
		if (i)
			rtn = open(file, O_APPEND | O_CREAT | O_WRONLY, 0777);
		else
			rtn = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	else
		rtn = open(file, O_RDONLY);
	if (rtn < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(file);
		exit(1);
	}
	return (rtn);
}

void	take_outfile(t_cmd *fakecmd)
{
	int	i;
	int	file_d;

	i = 0;
	while (fakecmd->outfile && fakecmd->outfile[i])
	{
		file_d = ft_open(fakecmd->outfile[i], 1, fakecmd->append[i]);
		dup2(file_d, 1);
		close(file_d);
		i++;
	}
}

void	take_infile(t_cmd *fakecmd)
{
	int	i;
	int	file_d;

	i = 0;
	if (fakecmd->heredoc_delim && fakecmd->heredoc_delim[0])
		ft_heredoc(fakecmd, 0, 0);
	else
	{
		while (fakecmd->infile[i])
		{
			file_d = ft_open(fakecmd->infile[i], 0, 0);
			dup2(file_d, 0);
			close(file_d);
			i++;
		}
	}
}

void	print_export_line(t_stack *node)
{
	if (node->value)
		printf("declare -x %s%c%c%s%c\n",
			node->var, node->equals, node->nail, node->value, node->nail);
	else
		printf("declare -x %s\n", node->var);
}
