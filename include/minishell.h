/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:48:37 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/16 21:49:45 by skaynar          ###   ########.fr       */
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
#include <fcntl.h>
#include <dirent.h>   // opendir, readdir, closedir
#include <sys/stat.h> // stat

typedef struct s_shell
{
    char **temp;
    char *read;
    char **main_env;
    int exit_status;
    struct s_stack	**env;
    struct s_stack	**env_exp;
}              t_shell;

typedef struct s_stack
{
    char            *var;
	char            *value;
    char             equals;
    char            nail;
	struct s_stack	*next;
}					t_stack;

typedef struct s_pipe
{
    char *cmd;
    char **args;
    char *infile;
    int  in_fd;
    char *outfile;
    int  out_fd;
    bool append;
    char *heredoc_delim;
    struct s_pipe   *next;
    int pipe;
}               t_pipe;


void shell_init(t_shell *shell , char **env);
// builtin
int is_builtin(t_shell *shell);
void builtin(t_shell *shell, t_stack **env, t_stack **env_exp);
int ft_n(char *str , char *n);
void cmd_env(t_stack **env);
void cmd_export(char **temp, t_stack **env, t_stack **env_exp, int i);
void cmd_unset(t_stack **env, t_stack **env_exp, char **temp);
void cmd_exit(t_shell *shell, char **str);

// komut çalıştırma 
void startpipe(t_pipe **pipe, t_shell *shell);
void no_pipe(t_pipe **pipe, t_shell *shell);
//
char	*ft_get_cmd(char *cmd, char **ep);
char	*ft_get_path(char **ep);
int	ft_access(char *exec, char **opt, char **path);


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
char    **copy_array(char **env);


#endif