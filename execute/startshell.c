/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:55:45 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/04 15:59:51 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_init(t_shell *shell, char **enveiroment)
{
	shell->main_env = enveiroment;
	shell->exit_status = 0;
	shell->env = malloc(sizeof(t_stack *));
	shell->env_exp = malloc(sizeof(t_stack *));
	*(shell->env_exp) = NULL;
	*(shell->env) = NULL;
	create_stack(shell, enveiroment);
}
