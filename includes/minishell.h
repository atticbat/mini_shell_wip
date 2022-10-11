/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:23:30 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/11 18:39:53 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "get_next_line.h"
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include "readline.h"
# include "history.h"
# include <errno.h>
# include <stdbool.h>
# include <limits.h>
# include "libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# define PROMPT "minishell $ "
# define HEREDOC "> "
# define WHITESPACE "\t\r\n\v "
# define QUOTES "\"\'"
# define TOKENS "<|>&"
# define OPERATOR "+-|<>"
# define REDIRECTIONS "+-<>"
# define BASH_NULL ""
# define EXPO_ERROR "\\-*#@!"

/* Nomenclature for type of cmd's asked  */
# define ECHO_CMD 1
# define CD_CMD 2
# define PWD_CMD 3
# define EXPORT_CMD 4
# define UNSET_CMD 5
# define ENV_CMD 6
# define EXIT_CMD 7
# define EXTER_CMD 8
/* defines for pipe */
# define READ_END   0
# define WRITE_END  1
# define PATH_FILE_1  ".fileout_temp"

# define DEFAULT_ERR 1
# define NOFILE_ERR 2
# define FAILFORK_ERR 11
# define MALLOC_ERR 12
# define PERMISSION_ERR 13
//not sure about this one, just have found this from testing
# define INVALID_EXIT_ERR 255
# define SYNTAX_ERR 258

typedef struct s_token
{
	char			type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	int				user_set;
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_matrix
{
	char			operator;
	char			**matrix;
	struct s_matrix	*next;
}	t_matrix;

typedef struct s_execute
{
	int		pipe[2];
	int		saved_stdout;
	int		*pids;
	int		pipe_count;
	int		current_pipe;
	int		status;
	char	*last_arg;
	char	last_op;
	int		heredoc_n;
}	t_execute;

typedef struct s_general
{
	int			error_no;
	int			to;
	int			from;
	int			flag;
	int			cmd_flag;
	char		*in;
	t_token		*tokens;
	t_matrix	*matrix;
	t_env		*envp;
	int			last_funct;
	int			last_return;
	int			builtin_flag;
}	t_general;

/* utilities */
void		reset(t_general *gen);
void		free_all(t_general *gen);
void		remove_files(void);
/* format checks */
int			check_variable_export(char *var);
int			check_variable(char *var);
int			check_variable_char(char c);
int			check_arg_char(char c);
int			check_exception_char(char c);
int			check_numeric(char *str);
/* string operations */
int			check_arg_end(char *in);
char		*append_space(char *in, char *str, int to);
char		*get_name(char *it);
int			check_equals(char *var);
int			check_invalid_quote(char *in, int to);
/* initial parsing */
int			find_token(t_general *gen);
int			extract_quote_node(t_general *gen);
int			extract_var_node(t_general *gen);
int			extract_arg_node(t_general *gen);
int			find_final_arg(t_general *gen);
int			extract_token_node(t_general *gen);
/* linked list token */
void		token_add_back(t_token **lst, t_token *new);
void		token_add_front(t_token **lst, t_token *new);
void		token_clear(t_token **lst, void (*del)(void *));
void		token_delone(t_token *lst, void (*del)(void *));
t_token		*token_last(t_token *lst);
t_token		*token_new(char type, char *content);
int			token_size(t_token *lst);
/* variable expansion */
int			expand_variable(t_general *gen);
char		*expand_dquote(char *content, t_env *envp, int last_return);
char		*extract_q_mark(char *content, int start, int last_return);
char		*extract_variable(char *content, int *i, t_env *envp);
char		*extract_regular(char *content, int *i, int start, t_env *envp);
char		*extract_bracketed(char *content, int *i, int start, t_env *envp);
void		merge_nodes(t_general *gen);
/* helper */
void		print_all_token(t_token *lst);
void		print_all_matrix(t_matrix *lst);
void		print_execute(t_execute lst);
char		*get_next_line(int fd);
/* echo */
void		ft_echo(char **it);
/* cd */
int			ft_cd(t_general *gen);
/* pwd */
char		*ft_pwd(char *buff);
/* env */
int			copy_envp(char **envp, t_general *gen);
int			count_envp(t_env *envp);
char		*extract_env_content(char *str);
char		*extract_env_name(char *str);
void		ft_env(t_env *envp);
char		*generate_env(t_env *envp);
char		*ft_getenv(t_env *envp, char *search);
t_env		*find_env(t_env *envp, char *search);
/* export */
void		ft_export(t_token *it, t_general *gen);
void		export_print_vars(t_env *envp);
int			ft_export_replace_exe(t_env **envp, char *add, char *name);
int			ft_export_replace_two(t_env **envp, char *add, char *name);
/* unset */
void		ft_unset(t_token *it, t_general *gen);
/* parse_function */
int			parse_function(t_general *gen);
void		toggle_arg(t_general *gen, int (*f)(char));
/* CHECKER FUNCTION */
void		check_cmd(t_token **inpt, int flag);
int			check_format(t_token *in);
int			cmd_searchlst(char *content);
int			cmd_check_contained(t_token *head);
int			check_variable_str(char *str);
int			check_file(char *arg);
/* linked list env */
void		env_add_back(t_env **lst, t_env *new);
void		env_add_front(t_env **lst, t_env *new);
void		env_clear(t_env **lst, void (*del)(void *));
void		env_delone(t_env *lst, void (*del)(void *));
t_env		*env_last(t_env *lst);
t_env		*env_new(char *name, char *content, int user_set);
void		env_find(t_general *gen, char *search);
int			env_size(t_env *lst);
/* linked list matrix */
void		matrix_add_back(t_matrix **lst, t_matrix *new);
void		matrix_add_front(t_matrix **lst, t_matrix *new);
void		matrix_clear(t_matrix **lst, void (*del)(void *));
void		matrix_delone(t_matrix *lst, void (*del)(void *));
t_matrix	*matrix_last(t_matrix *lst);
t_matrix	*matrix_new(char operator, char **matrix);
/* utility matrix */
void		create_matrix(t_token **it, t_general *gen);
char		**extract_matrix(t_token **it);
void		skip_multiple_ins(t_token **it, t_general *gen);
char		find_next_operator(t_matrix *matrix, char *search);
/* signals */
void		set_listeners(void);
void		interrupt_handler_child(int signum);
/* error handling */
int			handle_error(int error, t_general *gen);
int			error_extract_var(t_general *gen);
/* find path */
int			check_env(char *content);
char		*find_path_str(char *name, t_env **envp);
void		free_paths(char **paths);
/* execute */
int			execute_prep(t_general *gen);
int			builtin_executions(t_general *gen);
/* pipe */
int			count_operators(t_matrix *matrix, char *dataset);
void		exe_cmd(t_matrix *matrix, t_execute *exevars, t_general *gen);
void		execute(char **arg, t_env *envp);
int			redirect(t_matrix **it, t_execute *exevars);
void		exe_pipe(t_matrix *matrix, t_execute *exevars, t_env *envp);
void		exe_heredoc(t_matrix *matrix, t_execute *exevars, t_env *envp, \
	int heredoc_n);
void		ft_heredoc(char *str, t_env *envp, int heredoc_n);
void		read_heredoc(t_execute *exevars);
int			find_pipes(t_matrix *matrix);

#endif
