/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:12:30 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/12 17:25:17 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void cmd_pwd()
{
    char *pwd;
    pwd = getcwd(NULL,0);
    printf("%s\n", pwd);
    free(pwd);
}

void    cmd_cd(char **cd)
{
    struct stat info;

    if(sizeof_array(cd) > 2)
        printf("bash: cd: too many arguments\n");
    else if(sizeof_array(cd) == 1 || ft_strcmp(cd[1], "~") == 0 )
        chdir(getenv("HOME"));
    else if (stat(cd[1], &info) != 0)
        printf("bash: cd: %s: No such file or directory\n", cd[1]);
    else if (!S_ISDIR(info.st_mode))
        printf("bash: cd: %s: Not a directory\n", cd[1]);
    else
        chdir(cd[1]); 
}

void	cmd_echo(char **args)
{
	int	i;
	bool newline;
    
    newline = true;
    i = 1;    
	if (!args)
        return ;
	while (args[i] && ft_n(args[i], "-n") == 0)
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

void builtin(t_shell *shell, t_stack **env, t_stack **env_exp)
{
    if(ft_strcmp(shell->temp[0], "echo") == 0)
        cmd_echo(shell->temp);
    else if(ft_strcmp(shell->temp[0], "cd") == 0)
        cmd_cd(shell->temp);
    else if(ft_strcmp(shell->temp[0], "pwd") == 0)
        cmd_pwd();
    else if(ft_strcmp(shell->temp[0], "export") == 0)
        cmd_export(shell->temp, env, env_exp, 1);
    else if(ft_strcmp(shell->temp[0], "unset") == 0)
        cmd_unset(env, env_exp, shell->temp);
    else if(ft_strcmp(shell->temp[0], "env") == 0)
            cmd_env(env);
    else if(ft_strcmp(shell->temp[0], "exit") == 0)
        cmd_exit(shell, shell->temp);
    else
        return;
}

int is_builtin(t_shell *shell)
{
    char **temp;
    
    temp = ft_split(shell->read , ' ');
    shell->temp = temp;
    if(!temp[0])
        return(0);
    if(ft_strcmp(temp[0], "echo") == 0)
        return(1);
    else if(ft_strcmp(temp[0], "cd") == 0)
        return(1);
    else if(ft_strcmp(temp[0], "pwd") == 0)
        return(1);
    else if(ft_strcmp(temp[0], "export") == 0)
        return(1);
    else if(ft_strcmp(temp[0], "unset") == 0)
        return(1);
    else if(ft_strcmp(temp[0], "env") == 0)
        return(1);
    else if(ft_strcmp(temp[0], "exit") == 0)
        return(1);
    else
        return(0);
}
// ◦ export with no options
// ◦ unset with no options
// ◦ exit with no options