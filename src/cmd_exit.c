/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:53:52 by skaynar           #+#    #+#             */
/*   Updated: 2025/06/17 17:37:35 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void cmd_exit(t_shell *shell, char **str)
{
    if(sizeof_array(str) > 2)
    {
        shell->exit_status = 0;
        exit(shell->exit_status);
    }
    else
    {
        shell->exit_status = ft_atoi(str[1]);
        exit(shell->exit_status);
    }
}