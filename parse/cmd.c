/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:05:32 by yesoytur          #+#    #+#             */
/*   Updated: 2025/06/05 22:53:39 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*tmp;

	current = head;
	while (current)
	{
		tmp = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->infile)
			free_double(current->infile);
		if (current->outfile)
			free_double(current->outfile);
		if (current->heredoc_delim)
			free(current->heredoc_delim);
		if (current->args)
			free_double(current->args);
		free(current);
		current = tmp;
	}
}

// Initializes cmds
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
	if (!(new->args) || !(new->infile) || !(new->outfile) || !(new->append))
		return (free_cmd(new), NULL);
	return (new);
}

// Adds cmds back
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

// Prints cmds for debugging
void	print_cmds(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		printf("----\n");
		if (cmd->cmd)
			printf("cmd: %s\n", cmd->cmd);
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("arg[%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}
		if (cmd->infile)
		{
			i = 0;
			while (cmd->infile[i])
			{
				printf("infile[%d]: %s\n", i, cmd->infile[i]);
				i++;
			}
		}
		if (cmd->outfile)
		{
			i = 0;
			while (cmd->outfile[i])
			{
				printf("outfile[%d]: %s\n", i, cmd->outfile[i]);
				i++;
			}
		}
		if (cmd->append)
		{
			i = 0;
			while (i < cmd->out_count)
			{
				printf("append[%d]: %d\n", i, cmd->append[i]);
				i++;
			}
		}
		if (cmd->heredoc_delim)
			printf("heredoc_delim: %s\n", cmd->heredoc_delim);
		printf("----\n");
		cmd = cmd->next;
	}
}
