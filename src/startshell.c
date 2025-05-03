/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:55:45 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/03 14:58:26 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void shell_init(t_shell *shell , char **env)
{
    char *read;
    
    shell->env = env;
    while (1)
    {
        read = readline("minishell ~ ");
        if (!read)
            break;
        if(is_builtin(read))
            builtin(read , shell);
        else
            printf("builtin değil\n");
        free(read);
    }
    (void)env;
}