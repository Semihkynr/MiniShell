/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:53:52 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/28 19:28:21 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void cmd_exit(t_shell *shell, char **str)
{
    if(sizeof_array(str) > 1)
        printf("%s\n%s\n","exit" , "bash: exit: too many arguments");
    else
    {
        
        exit(shell->exit_status);
    }
}