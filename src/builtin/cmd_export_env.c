/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:14:40 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/06 18:21:29 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void cmd_env(t_stack **env)
{
    t_stack *temp;
	temp = *env;
	while(temp)
	{
		printf("%s=%s\n", temp->var, temp->value);
		temp = temp->next;
	}

}

int add_check(char *str)
{
    char **split;
    int i;
    
    split = split_once(str, 0);
    i = 0;
    if (split[0] == NULL || split[0][0] == '\0' || ft_isdigit(split[0][0]))
        return (clear_array(split), 1);
    while (split[i])
	{
		if (!ft_isname(split[i][0]))
			return (clear_array(split), 1);
		i++;
	}
	return (clear_array(split), 0);
}
void add_export(t_stack **env_exp, char *temp)
{
    char **str;
    
    str = split_once(temp, 0);
    if(str[1] && str[1][0] != '\0')
		ft_lstadd_back(env_exp, ft_lstnew(ft_strdup(str[0]), ft_strdup(str[1])));
	else
    	ft_lstadd_back(env_exp, ft_lstnew(ft_strdup(str[0]), ""));
	clear_array(str);
    sort_env_list((*env_exp));
}

void cmd_export(char **temp, t_stack **env_exp)
{
    int i;
    
    i = 1;
    if(!temp[1])
    {
        sort_env_list((*env_exp));
        t_stack *temp;
	    temp = *env_exp;
	    while(temp)
	    {
	    	printf("%s=\"%s\"\n", temp->var, temp->value);
	    	temp = temp->next;
        }
    }
    else
    {
        while(temp[i])
        {
            if(add_check(temp[i]))
                printf("bash: export: `%s': not a valid identifier\n" , temp[i]);
            else
                add_export(env_exp, temp[i]);
            i++;
        }
    }
}

