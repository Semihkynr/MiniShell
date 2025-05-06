/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:55:45 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/06 16:56:03 by skaynar          ###   ########.fr       */
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
    char *read;
    t_stack **env;
    t_stack **env_exp;
	env = malloc(sizeof(t_stack *));
	env_exp = malloc(sizeof(t_stack *));
    env = create_stack(env, enveiroment);
    env_exp = create_stack(env_exp, enveiroment);
    while (1)
    {
        read = readline("minishell ~ ");
        add_history(read);
        if (!read)
            break;
        if(is_builtin(read))
        {
            builtin(read , shell ,env , env_exp);
            clear_array(shell->temp);
        }
        else
            printf("builtin değil\n");
        free(read);
    }
    (void)env;
}