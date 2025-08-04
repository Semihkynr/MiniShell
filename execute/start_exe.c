/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:33:21 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/04 16:12:32 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	only_command(t_cmd *fakecmd, t_shell *shell)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(1);
	saved_stdin = dup(0);
	take_infile(fakecmd);
	take_outfile(fakecmd);
	builtin(shell, fakecmd);
	if (fakecmd->outfile)
	{
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
	if (fakecmd->infile || (fakecmd->heredoc_delim
			&& fakecmd->heredoc_delim[0]))
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

void	ft_child(t_shell *shell, t_cmd *fakecmd, int *prev_fd, int *fd)
{
	take_infile(fakecmd);
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, 0);
		close(*prev_fd);
	}
	if (fakecmd->next)
	{
		close(fd[0]);
		dup2(fd[1], 1);
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

void	start_exe(t_shell *shell, int prev_fd, t_cmd *fakecmd)
{
	int		fd[2];
	pid_t	pid;

	if (sk_lstsize(shell->cmd) == 1 && is_valid_cmd(fakecmd->args[0]))
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
				exit(EXIT_FAILURE);
			if (pid == 0)
				ft_child(shell, fakecmd, &prev_fd, fd);
			else
				ft_parent(fakecmd, &prev_fd, fd, pid);
			fakecmd = fakecmd->next;
		}
	}
}
