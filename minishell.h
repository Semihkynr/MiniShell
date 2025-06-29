/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:34:54 by yesoytur          #+#    #+#             */
/*   Updated: 2025/06/30 00:20:35 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include "libft/libft.h"

extern int	g_exit_status;

typedef enum e_token_type
{
	T_UNKNOWN,
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**infile;
	char			**outfile;
	bool			*append;
	int 			out_count; // this can go when we have done printing cmds
	char			**heredoc_delim;
	struct s_cmd	*next;
}	t_cmd;

// signal handle
// void	sigint_handler(int sig);

// token functions

t_token	*init_token(void);
void	free_token(t_token *head);
void	add_token(t_token *head, t_token *new);
t_token	*assign_token(char *value, bool *quoted);
void	print_tokens(t_token *head);

// cmd functions

void	free_cmd(t_cmd *head);
t_cmd	*init_cmd(void);
void	add_cmd(t_cmd *head, t_cmd *new);
void	print_cmds(t_cmd *cmd);

// parse functions

int		ft_isspace(char c);
int		ft_iseq(const char *a, const char *b);
void	free_double(char **args);
void	print_file_error(char *file_name);
void	print_syntax_error(char *token, int mod);
void	skip_spaces(const char *input, int *i);
void	skip_until_chars(char *input, int *i, const char *delims);
void	skip_until_specials(char *input, int *i);
int		is_operator(char c);
int		is_valid_word_token(const char *str);
int		is_valid_cmd(const char *cmd);
char	*strjoin_and_free(char *s1, char *s2);
char	*extract_single_quote(char *input, int *i, int start, bool *quoted);
char	*extract_dollar(char *input, int *i, int start);
char	*extract_tilde(char *input, int *i, int start);
char	*dollar_expansion(char *input, int *i, int start);
char	*extract_double_quote(char *input, int *i, int start, bool *quoted);
char	*extract_double_inner(char *input, int *i, int start);
char	*extract_word(char *input, int *i, int start);
t_token	*extract_token(char *input, int *i);
t_token	*tokenize_word(char *input, int *i, bool *quoted);
t_token	*tokenize_operator(char *input, int *i);
t_token	*tokenizer(char *input);
int		lexer(t_token *tokens);
t_cmd	*ft_add_args(t_cmd *new, t_token *token);
t_cmd	*ft_add_cmd(t_cmd *new, t_token *token);
t_cmd	*ft_add_infile(t_cmd *new, t_token **token);
t_cmd	*ft_add_outfile(t_cmd *new, t_token **token, bool append);
t_cmd	*ft_add_heredoc(t_cmd *new, t_token **token);
t_cmd	*converter(t_token *token);
t_cmd	*parse(char *input);

// execute 

#include <fcntl.h>
#include <dirent.h>   // opendir, readdir, closedir
#include <sys/stat.h> // stat
#include <sys/wait.h>

typedef struct s_memblock
{
	void				*data;
	struct s_memblock	*next;
}	t_memblock;

typedef struct s_shell
{
    char **temp;
    char *read;
    char **main_env;
    int exit_status;
    struct s_stack	**env;
    struct s_stack	**env_exp;
    struct s_cmd	*cmd;
}              t_shell;

typedef struct s_stack
{
    char            *var;
	char            *value;
    char             equals;
    char            nail;
	struct s_stack	*next;
	t_memblock	*perm_mem; 
	t_memblock	*temp_mem;
}					t_stack;

void shell_init(t_shell *shell , char **env);
void start_exe(t_shell *shell, int prev_fd);
// builtin
void builtin(t_shell *shell, t_cmd *cmd);
int ft_n(char *str);
void    cmd_cd(t_cmd *cmd);
void cmd_env(t_stack **env);
void cmd_export(char **temp, t_stack **env, t_stack **env_exp, int i);
void cmd_unset(t_stack **env, t_stack **env_exp, char **temp);
void cmd_exit(t_shell *shell, char **str);

// komut çalıştırma 
void	ft_execute(char **commands, char **ep);
void ft_heredoc(t_cmd *fakecmd, int i, int fd);

// ortak yardımcı
void	clear_array(char **array);
int		sizeof_array(char **av);
int		ft_strcmp(char *s1, char *s2);
void	sort_env_list(t_stack *head);
void	swap_nodes(t_stack *a, t_stack *b);
void 	create_stack(t_stack **list , char **enveironment);
t_stack	*sk_lstnew(char *var , char *value);
void	sk_lstclear(t_stack **lst);
int		sk_lstsize(t_cmd *lst);
void	sk_lstadd_back(t_stack **lst, t_stack *new);
char	**split_once(const char *str, int i);
int		ft_isname(int c);
char    **copy_array(char **env);
void 	free_all(t_shell *shell);

#endif

// extractor functions will be divided
// skip functions may need some clenup
// double quote function needs some improvements
// when all of this is done tokenize_oprator() is needed