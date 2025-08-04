/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:54:55 by yesoytur          #+#    #+#             */
/*   Updated: 2025/08/04 16:13:23 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_add_args(t_cmd *new, t_token *token)
{
	int	i;

	i = 0;
	while (new->args[i])
		i++;
	if (i >= MAX_INPUT - 1)
		return (NULL);
	new->args[i] = ft_strdup(token->value);
	if (!(new->args[i]))
		return (NULL);
	return (new);
}

t_cmd	*ft_add_cmd(t_cmd *new, t_token *token)
{
	if (!new->cmd)
	{
		new->cmd = ft_strdup(token->value);
		if (!new->cmd)
			return (NULL);
	}
	return (ft_add_args(new, token));
}

t_cmd	*ft_add_infile(t_cmd *new, t_token **token)
{
	int	i;

	i = 0;
	while (new->infile[i])
		i++;
	if (!(*token)->next)
		return (NULL);
	*token = (*token)->next;
	if (access((*token)->value, F_OK | R_OK) != 0)
	{
		print_file_error((*token)->value);
		return (NULL);
	}
	new->infile[i] = ft_strdup((*token)->value);
	if (!new->infile[i])
		return (NULL);
	return (new);
}

t_cmd	*ft_add_outfile(t_cmd *new, t_token **token, bool append)
{
	int	i;

	i = 0;
	while (new->outfile[i])
		i++;
	if (!(*token)->next)
		return (NULL);
	*token = (*token)->next;
	if (access((*token)->value, F_OK) == 0 && access((*token)->value,
			W_OK) != 0)
	{
		print_file_error((*token)->value);
		return (NULL);
	}
	new->outfile[i] = ft_strdup((*token)->value);
	if (!new->outfile[i])
		return (NULL);
	new->append[i] = append;
	return (new);
}

t_cmd	*ft_add_heredoc(t_cmd *new, t_token **token)
{
	int	i;

	i = 0;
	while (new->heredoc_delim[i])
		i++;
	if (!(*token)->next)
		return (NULL);
	*token = (*token)->next;
	new->heredoc_delim[i] = ft_strdup((*token)->value);
	if (!new->heredoc_delim[i])
		return (NULL);
	return (new);
}
