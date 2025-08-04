/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:14:40 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/04 16:10:44 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_env(t_stack **env)
{
	t_stack	*temp;

	temp = *env;
	while (temp)
	{
		if (temp->value)
			printf("%s%c%s\n", temp->var, temp->equals, temp->value);
		else
			printf("%s\n", temp->var);
		temp = temp->next;
	}
}

int	is_there_same(t_stack **env_exp, char **str)
{
	t_stack	*fake;

	fake = *env_exp;
	while (fake)
	{
		if (ft_strcmp(fake->var, str[0]) == 0)
		{
			if (fake->value != 0 && str[1])
				free(fake->value);
			if (str[1] != 0)
			{
				fake->value = ft_strdup(str[1]);
				fake->equals = '=';
				fake->nail = '"';
			}
			return (1);
		}
		else
		{
			if (!fake->next)
				return (0);
			fake = fake->next;
		}
	}
	return (0);
}

int	add_check(char *str)
{
	char	**split;

	split = split_once(str, 0);
	if (split[0] == NULL || split[0][0] == '\0' || ft_isdigit(split[0][0]))
		return (clear_array(split), 1);
	return (clear_array(split), 0);
}

void	add_export(t_stack **env_exp, t_stack **env, char *temp)
{
	char	**str;

	str = split_once(temp, 0);
	if (!is_there_same(env_exp, str))
	{
		if (str[1])
			sk_lstadd_back(env_exp, sk_lstnew(ft_strdup(str[0]),
					ft_strdup(str[1])));
		else
			sk_lstadd_back(env_exp, sk_lstnew(ft_strdup(str[0]), NULL));
	}
	if (!is_there_same(env, str))
	{
		if (str[1])
			sk_lstadd_back(env, sk_lstnew(ft_strdup(str[0]),
					ft_strdup(str[1])));
	}
	clear_array(str);
	sort_env_list((*env_exp));
}

void	cmd_export(char **temp, t_stack **env, t_stack **env_exp, int i)
{
	t_stack	*tmp;

	if (!temp[1])
	{
		sort_env_list((*env_exp));
		tmp = *env_exp;
		while (tmp)
		{
			// if (tmp->value)
			// 	printf("declare -x %s%c%c%s%c\n", tmp->var, tmp->equals,
			// 		tmp->nail, tmp->value, tmp->nail);
			// else
			// 	printf("declare -x %s\n", tmp->var);
			tmp = tmp->next;
		}
	}
	else
	{
		while (temp[i])
		{
			if (add_check(temp[i]))
				// {
				// 	ft_putstr_fd("bash: export: '", 2);
				// 	ft_putstr_fd(temp[i], 2);
				// 	ft_putstr_fd("': not a valid identifier\n", 2);
				// }
				else add_export(env_exp, env, temp[i]);
			i++;
		}
	}
}
