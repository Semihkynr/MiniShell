/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:12:30 by skaynar           #+#    #+#             */
/*   Updated: 2025/07/23 18:02:57 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void cmd_pwd()
{
    char *pwd;
    pwd = getcwd(NULL,0);
    printf("%s\n", pwd);
    free(pwd);
}

void    cmd_cd(t_cmd *cmd)
{
    struct stat info;
    if(sizeof_array(cmd->args) > 2)
    {
        ft_putstr_fd("bash: cd: too many arguments\n", 2);
	    set_exit_status_code(1);
    }
    else if(sizeof_array(cmd->args) == 1 || ft_strncmp(cmd->args[1], "~", 1) == 0 )
        chdir(getenv("HOME"));
    else if (stat(cmd->args[1], &info) != 0)
    {
        ft_putstr_fd("bash: cd: ", 2);
        ft_putstr_fd(cmd->args[1], 2);
        ft_putstr_fd(": No such file or directory\n",2);
    }
    else if (!S_ISDIR(info.st_mode))
    {
        ft_putstr_fd("bash: cd: ", 2);
        ft_putstr_fd(cmd->args[1], 2);
        ft_putstr_fd(": Not a directory\n", 2);
    }
    else
        chdir(cmd->args[1]);
}

void	cmd_echo(char **args)
{
	int	i;
	bool newline;
    
    newline = true;
    i = 1;
	if (!args)
        return ;
	while (args[i] && ft_n(args[i]) == 0)
	{
		newline = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

void builtin(t_shell *shell, t_cmd *cmd)
{
    if(ft_strcmp(cmd->cmd, "echo") == 0)
        cmd_echo(cmd->args);
    else if(ft_strcmp(cmd->cmd, "cd") == 0)
        cmd_cd(cmd);
    else if(ft_strcmp(cmd->cmd, "pwd") == 0)
        cmd_pwd();
    else if(ft_strcmp(cmd->cmd, "export") == 0)
        cmd_export(cmd->args, shell->env, shell->env_exp, 1);
    else if(ft_strcmp(cmd->cmd, "unset") == 0)
        cmd_unset(shell->env, shell->env_exp, cmd->args);
    else if(ft_strcmp(cmd->cmd, "env") == 0)
            cmd_env(shell->env);
    else if(ft_strcmp(cmd->cmd, "exit") == 0)
        ft_exit(shell);
    else
        return;
}

// ◦ export with no options
// ◦ unset with no options
// ◦ exit with no options