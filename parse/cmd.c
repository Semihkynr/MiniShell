/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:05:32 by yesoytur          #+#    #+#             */
/*   Updated: 2025/08/04 16:13:36 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->cmd)
			free(head->cmd);
		if (head->infile)
			free_double(head->infile);
		if (head->outfile)
			free_double(head->outfile);
		if (head->heredoc_delim)
			free_double(head->heredoc_delim);
		if (head->args)
			free_double(head->args);
		if (head->append)
			free(head->append);
		free(head);
		head = tmp;
	}
}

t_cmd	*init_cmd(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = ft_calloc(MAX_INPUT, sizeof(char *));
	new->infile = ft_calloc(MAX_INPUT, sizeof(char *));
	new->outfile = ft_calloc(MAX_INPUT, sizeof(char *));
	new->append = ft_calloc(MAX_INPUT, sizeof(bool));
	new->heredoc_delim = ft_calloc(MAX_INPUT, sizeof(char *));
	if (!(new->args) || !(new->infile) || !(new->outfile)
		|| !(new->append) || !(new->heredoc_delim))
		return (free_cmd(new), NULL);
	return (new);
}

void	add_cmd(t_cmd *head, t_cmd *new)
{
	t_cmd	*prev;

	if (!head || !new)
		return ;
	prev = head;
	while (prev->next)
		prev = prev->next;
	prev->next = new;
}
