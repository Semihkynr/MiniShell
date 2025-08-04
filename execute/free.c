/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:33:47 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/04 15:59:36 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->args)
			clear_array(tmp->args);
		if (tmp->infile)
			clear_array(tmp->infile);
		if (tmp->outfile)
			clear_array(tmp->outfile);
		if (tmp->append)
			free(tmp->append);
		if (tmp->heredoc_delim)
			clear_array(tmp->heredoc_delim);
		free(tmp);
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->read)
		free(shell->read);
	if (shell->env)
	{
		sk_lstclear(shell->env);
		free(shell->env);
	}
	if (shell->env_exp)
	{
		sk_lstclear(shell->env_exp);
		free(shell->env_exp);
	}
	if (shell->temp)
		clear_array(shell->temp);
	free(shell);
}
