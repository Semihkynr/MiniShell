/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:48:37 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/06 18:18:51 by skaynar          ###   ########.fr       */
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
    char **temp;
}              t_shell;

typedef struct s_stack
{
    char            *var;
	char            *value;
	struct s_stack	*next;
}					t_stack;

void shell_init(t_shell *shell , char **env);
// builtin
int is_builtin(char *read);
void builtin(char *read , t_shell *shell, t_stack **env, t_stack **env_exp);
void cmd_echo(char *echo);
int ft_n(char *str , char *n);
void cmd_env(t_stack **env);
void cmd_export(char **temp, t_stack **env_exp);
char    **copy_env(char **env);

// ortak yardımcı
void	clear_array(char **array);
int sizeof_array(char **av);
int	ft_strcmp(char *s1, char *s2);
void	sort_env_list(t_stack *head);
void	swap_nodes(t_stack *a, t_stack *b);
t_stack **create_stack(t_stack **list , char **enveironment);
t_stack	*ft_lstnew(char *var , char *value);
t_stack	*ft_lstlast(t_stack *lst);
void	ft_lstadd_back(t_stack **lst, t_stack *new);
int	ft_lstsize(t_stack *lst);
void	ft_lstclear(t_stack **lst);
char	**split_once(const char *str, int i);
int	ft_isname(int c);


#endif