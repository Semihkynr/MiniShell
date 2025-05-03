/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:48:37 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/03 18:16:06 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
// 
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
// 
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>   // opendir, readdir, closedir
#include <sys/stat.h> // stat

typedef struct s_shell
{
    char **env;
}              t_shell;

void shell_init(t_shell *shell , char **env);
// builtin
int is_builtin(char *read);
void builtin(char *read , t_shell *shell);
void cmd_echo(char *echo);
int ft_n(char *str , char *n);
void cmd_env(t_shell *shell);
void	cmd_export(t_shell *shell, char **env);

// ortak yardımcı
void	clear_array(char **array);
int sizeof_array(char **av);
int	ft_strcmp(char *s1, char *s2);



#endif