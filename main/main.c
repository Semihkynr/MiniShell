/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:38:00 by yesoytur          #+#    #+#             */
/*   Updated: 2025/08/07 22:09:49 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status = 0;

void	sigint_handler(int sig);

void	fake_main(t_shell *shell)
{
	t_cmd	*fakecmd;

	while (1)
	{
		shell->read = readline("minishell> ");
		if (!shell->read)
		{
			printf("exit\n");
			g_exit_status = 131;
			break ;
		}
		if (!(*shell->read))
		{
			free(shell->read);
			continue ;
		}
		add_history(shell->read);
		shell->cmd = parse(shell);
		if (!shell->cmd)
			g_exit_status = 2;
		fakecmd = shell->cmd;
		start_exe(shell, -1, fakecmd);
		free(shell->read);
		free_cmd_list(shell->cmd);
	}
}

int	main(int argc, char **argv, char **enveiroment)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
	{
		free_shell(shell);
		exit(1);
	}
	shell_init(shell, enveiroment);
	fake_main(shell);
	free_shell(shell);
	return (g_exit_status);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
