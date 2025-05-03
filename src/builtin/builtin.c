/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:12:30 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/03 18:17:22 by skaynar          ###   ########.fr       */
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

void    cmd_cd(char *cd)
{
    struct stat info;
    char **av;
    av = ft_split(cd , ' ');
    if(sizeof_array(av) > 2)
        printf("bash: cd: too many arguments\n");
    else if(sizeof_array(av) == 1 || ft_strcmp(av[1], "~") == 0 )
        chdir(getenv("HOME"));
    else if (stat(av[1], &info) != 0)
        printf("bash: cd: %s: No such file or directory\n", av[1]);
    else if (!S_ISDIR(info.st_mode))
        printf("bash: cd: %s: Not a directory\n", av[1]);
    else
        chdir(av[1]); 
}

void	cmd_echo(char *echo)
{
	char	**args;
	int	i;
	bool newline;
    
    newline = true;
    i = 1;
	args = ft_split(echo, ' ');
    
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
	clear_array(args);
}

void builtin(char *read , t_shell *shell)
{
    char **temp;
    temp = ft_split(read , ' ');
    
    if(ft_strcmp(temp[0], "echo") == 0)
        cmd_echo(read);
    else if(ft_strcmp(temp[0], "cd") == 0)
        cmd_cd(read);
    else if(ft_strcmp(temp[0], "pwd") == 0)
        cmd_pwd();
    // else if(ft_strcmp(temp[0], "export") == 0)
    // {
    //     cmd_export(shell, temp);
    // }
    // else if(ft_strcmp(temp[0], "unset") == 0)
    //     cmd_unset(split[0]);
    else if(ft_strcmp(temp[0], "env") == 0)
        cmd_env(shell);
    // else if(ft_strcmp(temp[0], "exit") == 0)
    //     cmd_exit(split[0]);
    else
        return;
}

int is_builtin(char *read)
{
    char **temp;
    temp = ft_split(read , ' ');
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
// echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options