/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:33:21 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/04 13:10:07 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open(char *file, int val, bool i)
{
    int	rtn;
    
	if (val)
    {
        if(i)
            rtn = open(file, O_APPEND | O_CREAT | O_WRONLY, 0777);
        else
            rtn = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    }
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
    int file_d;
    
    while (fakecmd->outfile && fakecmd->outfile[i])
    {
        file_d = ft_open(fakecmd->outfile[i], 1 , fakecmd->append[i]);
        dup2(file_d, 1);
        close(file_d);
        i++;
    }
}

void take_infile(t_cmd *fakecmd)
{
    int i;
    i = 0;
    int file_d;
    if(fakecmd->heredoc_delim && fakecmd->heredoc_delim[0])
        ft_heredoc(fakecmd, 0, 0);
    else
    {
        while(fakecmd->infile[i])
        {
            file_d = ft_open(fakecmd->infile[i], 0, 0);
            dup2(file_d, 0);
            close(file_d);
            i++;
        }
    }
}

void only_command(t_cmd *fakecmd, t_shell *shell)
{
    int saved_stdout = dup(1); // stdout'u yedekle
    int saved_stdin = dup(0);  // stdin'i yedekle

    take_infile(fakecmd);      // stdin yönlendir
    take_outfile(fakecmd);     // stdout yönlendir
    builtin(shell, fakecmd);   // komutu çalıştır
    if (fakecmd->outfile)
    {
        dup2(saved_stdout, 1);
        close(saved_stdout);
    }
    if (fakecmd->infile || (fakecmd->heredoc_delim && fakecmd->heredoc_delim[0]))
    {
        dup2(saved_stdin, 0);
        close(saved_stdin);
    }
}

void	ft_parent(t_cmd *fakecmd, int *prev_fd, int *fd, pid_t pid)
{
	int	status;

	if (*prev_fd != -1)
		close(*prev_fd);
	if (fakecmd->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
}

void ft_child(t_shell *shell, t_cmd *fakecmd, int *prev_fd , int *fd)
{
    take_infile(fakecmd);
    if (*prev_fd != -1)
    {
        dup2(*prev_fd, 0);   // önceki pipe'ın çıkışı -> stdin
        close(*prev_fd);
    }
    if (fakecmd->next)
    {
        close(fd[0]);
        dup2(fd[1], 1); // stdout -> yeni pipe'ın çıkışı
        close(fd[1]);
    }
    take_outfile(fakecmd);
    if (is_valid_cmd(fakecmd->args[0]))
        builtin(shell, fakecmd);
    else
        ft_execute(fakecmd->args, shell->main_env, shell);
    free_cmd_list(shell->cmd);
    free_shell(shell);
    exit(EXIT_SUCCESS);
}

void start_exe(t_shell *shell, int prev_fd)
{
    t_cmd	*fakecmd;
    int		fd[2];
    pid_t	pid;

    fakecmd = shell->cmd;    
    if(sk_lstsize(shell->cmd) == 1 && is_valid_cmd(fakecmd->args[0]))
        only_command(fakecmd, shell);
    else
    {
        while (fakecmd)
        {
            if (fakecmd->next && pipe(fd) < 0)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            pid = fork();
            if (pid < 0)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (pid == 0)
                ft_child(shell,fakecmd,&prev_fd,fd);
            else
                ft_parent(fakecmd,&prev_fd,fd,pid);
            fakecmd = fakecmd->next;
        }
    }
}
