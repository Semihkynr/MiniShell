/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:07:47 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/04 15:22:45 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*get_exit_status_code(void)
{
	static int	exit_status = 0;

	return (&exit_status);
}

void	set_exit_status_code(int status)
{
	*get_exit_status_code() = status;
}

int	is_numeric(char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	exit_helper(t_shell *shell , int *exit_code)
{
	int	num;

	if (is_numeric(shell->cmd->args[1]))
	{
		num = ft_atoi(shell->cmd->args[1]);
		*exit_code = (unsigned char)num;
		set_exit_status_code(*exit_code);
	}
	else
	{
		write(2, "minishell: exit: ", 18);
		write(2, shell->cmd->args[1], ft_strlen(shell->cmd->args[1]));
		write(2, ": numeric argument required\n", 29);
		set_exit_status_code(2);
    	free_cmd_list(shell->cmd);
		free_shell(shell);
		exit(2);
	}
}
// "/home/skaynar/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin:/home/skaynar/.dotnet/tools:/home/skaynar/.local/bin:/home/skaynar/.local/bin:/home/skaynar/.venv/bin:/home/skaynar/.venv/bin"


int	ft_exit(t_shell *shell)
{
	int	argc;
	int	exit_code;

	argc = 0;
	exit_code = 0;
	while (shell->cmd->args[argc])
		argc++;
	printf("exit\n");
	if (argc == 1)
		exit_code = *get_exit_status_code();
	else if (argc == 2 || !is_numeric(shell->cmd->args[1]))
		exit_helper(shell, &exit_code);
	else
	{
		write(2, "minishell: too many arguments\n", 31);
		set_exit_status_code(1);
		g_exit_status = 1;
		return (1);
	}
    free_cmd_list(shell->cmd);
	free_shell(shell);
	exit(exit_code);
	return (0);
}
