/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:33:21 by skaynar           #+#    #+#             */
/*   Updated: 2025/06/12 15:05:36 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open(char *file, int val)
{
    int	rtn;
    
	if (val)
        rtn = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
        rtn = open(file, O_RDONLY);
	if (rtn < 0)
	{
        ft_putstr_fd("bash: ", 2);
		perror(file);
		exit(1);
	}
	return (rtn);
}

void take_outfile(t_cmd *fakecmd)
{
    int i = 0;
    while (fakecmd->outfile && fakecmd->outfile[i])
    {
        int file_d = ft_open(fakecmd->outfile[i], 1);
        dup2(file_d, 1);
        close(file_d);
        i++;
    }
}

void take_infile(t_cmd *fakecmd)
{
    int i = 0;
    while(fakecmd->infile[i])
    {
        int	file_d;

        file_d = ft_open(fakecmd->infile[i], 0);
        dup2(file_d, 0);
        close(file_d);	
        i++;
    }
}
void last_command(t_shell *shell, t_cmd *fakecmd, int *fd)
{
    take_infile(fakecmd);
    dup2(fd[0], 0);       // stdin'i pipe'ın read ucuna yönlendir
    close(fd[1]);         // write ucunu kapat (bu child için)
    take_outfile(fakecmd);
    if(is_valid_cmd(fakecmd->args[0]))
        builtin(shell, fakecmd);
    else
        ft_execute(fakecmd->args, shell->main_env);
}

void much_command(t_shell *shell, t_cmd *fakecmd, int *fd)
{    
    take_infile(fakecmd);
    dup2(fd[1], 1);
    close(fd[0]); 
    take_outfile(fakecmd); 
    if(is_valid_cmd(fakecmd->args[0]))
        builtin(shell, fakecmd);
    else
        ft_execute(fakecmd->args, shell->main_env);
}

void only_command(t_cmd *fakecmd, t_shell *shell)
{
    take_infile(fakecmd);
    take_outfile(fakecmd);
    if((ft_strcmp(fakecmd->cmd, "export") == 0))
        cmd_export(fakecmd->args, shell->env, shell->env_exp, 1);
    else if ((ft_strcmp(fakecmd->cmd, "unset") == 0))
        cmd_unset(shell->env, shell->env_exp, fakecmd->args);
    else
        cmd_cd(fakecmd);
}

void start_exe(t_shell *shell)
{
    int size;
    t_cmd *fakecmd;
    int fd[2];
    pid_t	pid;
    
    size = sk_lstsize(shell->cmd);
    fakecmd = shell->cmd;

    if(size == 1 && ((ft_strcmp(fakecmd->args[0], "cd") == 0) 
        || (ft_strcmp(fakecmd->args[0], "export") == 0)
        || (ft_strcmp(fakecmd->args[0], "unset") == 0)))
        only_command(fakecmd, shell);
    else
    {
        while (fakecmd)
        {
            if(pipe(fd) < 0)
                printf("pipe hatasi\n");
            pid = fork();
            if (pid == 0)
            {
                if (fakecmd->next)
                    much_command(shell, fakecmd, fd);
                else
                    last_command(shell, fakecmd, fd);
                exit(EXIT_SUCCESS);
            }
            else
            {
                if (fakecmd->next)
                    close(fd[1]);
                waitpid(pid, NULL, 0);
                fakecmd = fakecmd->next;
            }
        }
    }
}
