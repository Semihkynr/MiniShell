/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:38:00 by yesoytur          #+#    #+#             */
/*   Updated: 2025/07/07 01:01:24 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status = 0;

void	sigint_handler(int sig);

int	main(int argc, char **argv, char **enveiroment)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler); // for ctrl + c (prints newline)
	signal(SIGQUIT, SIG_IGN); // for ctrl + / (does nothing)
	t_shell *shell;
	// int a = 0;
    shell = ft_calloc(1 , sizeof(t_shell));
    if(!shell)
		exit(0);
	shell_init(shell, enveiroment);
	while (1)
	{
		shell->read = readline("minishell> ");
		if (!shell->read) // for ctrl + d (prints exit\n and quits)
		{
			printf("exit\n");
			break;
		}
		if (!(*shell->read)) // for Enter (reads again)
		{
			free(shell->read);
			continue ;
		}
		add_history(shell->read);
		shell->cmd = parse(shell->read);
		start_exe(shell, -1);
		free(shell->read);
		free_cmd_list(shell->cmd);
		free(shell->cmd);
	}
	free_shell(shell);
	free(shell);
	return (0);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
