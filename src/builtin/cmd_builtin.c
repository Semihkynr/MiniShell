// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cmd_builtin.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/03 15:18:28 by skaynar           #+#    #+#             */
// /*   Updated: 2025/05/03 18:16:44 by skaynar          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../include/minishell.h"

void cmd_env(t_shell *shell)
{
    int i;
    i = 0;
    while (shell->env[i])
    {
        printf("%s\n",shell->env[i]);
        i++;
    }  
}

// void	swap(char **a, char **b)
// {
// 	char *tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }

// void	sort_env(char **env)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (env[i])
// 	{
// 		j = i + 1;
// 		while (env[j])
// 		{
// 			if (strcmp(env[i], env[j]) > 0)
// 				swap(&env[i], &env[j]);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	cmd_export(t_shell *shell, char **env)
// {
//     int i;
//     char **new_env;
    
//     i = 0;
//     if(!env[1])
//     {
        
//     }
// 	shell->env = new_env;
// 	sort_env(shell->env);
// 	i = 0;
// 	while (shell->env[i])
// 	{
// 		printf("declare -x %s\n", shell->env[i]);
// 		i++;
// 	}
// }
