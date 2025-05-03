/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:54:19 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/02 17:42:04 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int ac , char **av , char **env)
{
    if (ac > 1)
	{
		printf("minishell: %s: No such file or directory\n", av[1]);
		return (127);
	}
    t_shell *shell;
    shell = ft_calloc(1 , sizeof(t_shell));
    if(!shell)
        exit(0);
    shell_init(shell , env);
    return(0);
}
