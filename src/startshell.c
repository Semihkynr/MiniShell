/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:55:45 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/16 22:53:29 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void realenv(char **a)
{
    int i = 0;
    while (a[i])
    {
        printf("REALL -> %s\n",a[i]);
        i++;
    }
}
void shell_init(t_shell *shell , char **enveiroment)
{
    t_pipe **pipe;
    shell->main_env = enveiroment;
    shell->exit_status = 0;
    pipe = malloc(sizeof(t_pipe *));
    *pipe = malloc(sizeof(t_pipe));
	shell->env = malloc(sizeof(t_stack *));
	shell->env_exp = malloc(sizeof(t_stack *));
    shell->env = create_stack(shell->env, enveiroment);
    shell->env = create_stack(shell->env_exp, enveiroment);
    while (1)
    {
        int a = 1;
        shell->read = readline("minishell ~ ");
        add_history(shell->read);
        if (!shell->read)
            break;
        if(is_builtin(shell))
            builtin(shell ,shell->env , shell->env_exp);
        else
        {
            if(a == 1)
                no_pipe(pipe, shell);
            else
                // many_cmd(pipe);
                printf("cok komut\n");
        }
        free(shell->read);
    }
    if(shell->read)
        free(shell->read);
    ft_lstclear(shell->env);
    ft_lstclear(shell->env_exp);
}
