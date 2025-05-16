/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nopipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:51:10 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/16 23:09:51 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

void startpipe(t_pipe **pipe, t_shell *shell)
{
    t_pipe *a;
    a = *pipe;

    a->cmd = ft_strdup(ft_get_cmd(shell->read, shell->main_env));
    a->args = shell->temp;
    if (!a->args)
        return ;
    a->infile = NULL;
    a->in_fd = -1;
    a->outfile = NULL;
    a->out_fd = -1;
    a->append = false;
    a->next = NULL;
    a->pipe = 0;
}

void    execute_cmd(t_pipe *cmd, char **envp)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (cmd->infile)
        {
            cmd->in_fd = open(cmd->infile, O_RDONLY);
            if (cmd->in_fd < 0)
            {
                perror("infile");
                exit(EXIT_FAILURE);
            }
            dup2(cmd->in_fd, STDIN_FILENO);
        }
        if (cmd->outfile)
        {
            int flags = O_WRONLY | O_CREAT | (cmd->append ? O_APPEND : O_TRUNC);
            cmd->out_fd = open(cmd->outfile, flags, 0644);
            if (cmd->out_fd < 0)
            {
                perror("outfile");
                exit(EXIT_FAILURE);
            }
            dup2(cmd->out_fd, STDOUT_FILENO);
        }
        execve(cmd->cmd, cmd->args, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, NULL, 0);
        if (cmd->in_fd != -1)
            close(cmd->in_fd);
        if (cmd->out_fd != -1)
            close(cmd->out_fd);
    }
}

void no_pipe(t_pipe **pipe, t_shell *shell)
{
    startpipe(pipe, shell);
    if(is_builtin(shell))
        builtin(shell ,shell->env , shell->env_exp);
    else
        execute_cmd(*pipe, shell->main_env);
}