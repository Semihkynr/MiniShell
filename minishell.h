/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:34:54 by yesoytur          #+#    #+#             */
/*   Updated: 2025/08/04 17:56:32 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

extern int	g_exit_status;

typedef struct s_shell
{
	char			**temp;
	char			*read;
	char			**main_env;
	int				exit_status;
	struct s_stack	**env;
	struct s_stack	**env_exp;
	struct s_cmd	*cmd;
}					t_shell;

typedef enum e_token_type
{
	T_UNKNOWN,
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			quoted;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**infile;
	char			**outfile;
	bool			*append;
	char			**heredoc_delim;
	struct s_cmd	*next;
}					t_cmd;

t_token				*init_token(void);
void				free_token(t_token *head);
void				add_token(t_token *head, t_token *new);
t_token				*assign_token(char *value, bool *quoted);

void				free_cmd(t_cmd *head);
t_cmd				*init_cmd(void);
void				add_cmd(t_cmd *head, t_cmd *new);

int					ft_isspace(char c);
int					ft_iseq(const char *a, const char *b);
void				free_double(char **args);
void				print_file_error(char *file_name);
void				print_syntax_error(char *token, int mod);
void				skip_spaces(const char *input, int *i);
void				skip_until_chars(char *input, int *i, const char *delims);
void				skip_until_specials(char *input, int *i);
int					is_operator(char c);
int					is_valid_word_token(const char *str);
int					is_valid_cmd(const char *cmd);
char				*strjoin_and_free(char *s1, char *s2);
char				*extract_single_quote(char *input, int *i, int start,
						bool *quoted);
char				*extract_dollar(t_shell *shell, int *i, int start);
char				*extract_tilde(t_shell *shell, int *i, int start);
char				*dollar_expansion(t_shell *shell, int *i, int start);
char				*extract_double_quote(t_shell *shell, int *i, int start,
						bool *quoted);
char				*extract_double_inner(t_shell *shell, int *i, int start);
char				*extract_word(char *input, int *i, int start);
t_token				*extract_token(t_shell *shell, int *i);
t_token				*tokenize_word(t_shell *shell, int *i, bool *quoted);
t_token				*tokenize_operator(char *input, int *i);
t_token				*tokenizer(t_shell *shell);
int					lexer(t_token *tokens);
t_cmd				*ft_add_args(t_cmd *new, t_token *token);
t_cmd				*ft_add_cmd(t_cmd *new, t_token *token);
t_cmd				*ft_add_infile(t_cmd *new, t_token **token);
t_cmd				*ft_add_outfile(t_cmd *new, t_token **token, bool append);
t_cmd				*ft_add_heredoc(t_cmd *new, t_token **token);
t_cmd				*converter(t_token *token);
t_cmd				*parse(t_shell *shell);

typedef struct s_stack
{
	char			*var;
	char			*value;
	char			equals;
	char			nail;
	struct s_stack	*next;
}					t_stack;

void				shell_init(t_shell *shell, char **env);
void				start_exe(t_shell *shell, int prev_fd, t_cmd *fakecmd);
void				builtin(t_shell *shell, t_cmd *cmd);
int					ft_n(char *str);
void				cmd_cd(t_cmd *cmd, t_shell *shell);
void				cmd_env(t_stack **env);
void				cmd_export(char **temp, t_stack **env, t_stack **env_exp,
						int i);
void				cmd_unset(t_stack **env, t_stack **env_exp, char **temp);
void				ft_execute(char **commands, char **ep, t_shell *shell);
char				*find_value(t_stack **stack, char *name);
void				ft_heredoc(t_cmd *fakecmd, int i, int fd);

int					sizeof_array(char **av);
int					ft_strcmp(char *s1, char *s2);
void				sort_env_list(t_stack *head);
void				swap_nodes(t_stack *a, t_stack *b);
void				create_stack(t_shell *shell, char **enveironment);
t_stack				*sk_lstnew(char *var, char *value);
int					sk_lstsize(t_cmd *lst);
void				sk_lstadd_back(t_stack **lst, t_stack *new);
char				**split_once(const char *str, int i);
int					ft_isname(int c);
char				**copy_array(char **env);
int					ft_open(char *file, int val, bool i);
void				take_outfile(t_cmd *fakecmd);
void				take_infile(t_cmd *fakecmd);

void				free_shell(t_shell *shell);
void				clear_array(char **array);
void				sk_lstclear(t_stack **lst);
void				free_cmd_list(t_cmd *cmd);
int					ft_exit(t_shell *shell);
void				exit_helper(t_shell *shell, int *exit_code);
int					is_numeric(char *str);
void				set_exit_status_code(int status);
int					*get_exit_status_code(void);

#endif
