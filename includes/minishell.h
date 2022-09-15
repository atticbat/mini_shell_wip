/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:23:30 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/15 18:17:56 by aparedes         ###   ########.fr       */
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
// # include <termios.h>
# include "readline.h"
# include "history.h"
# include <errno.h>
# include <stdbool.h>
# include <limits.h>
# include "libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# define PROMPT "minishell $ "
# define HEREDOC "heredoc> "
# define WHITESPACE "\t\r\n\v "
# define QUOTES "\"\'"
# define TOKENS "<|>&"
# define OPERATOR "+-&|<>"
# define REDIRECTIONS "+-<>"
# define BASH_NULL ""
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
# define PATH_FILE_1  "fileout_temp"

typedef struct s_token
{
	char			type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
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
	char			**arg1;
	char			**arg2;
	char			operator;
	char			*res_exe;
}	t_execute;

typedef struct s_general
{
	int			error_no;
	int			to;
	int			from;
	int			flag;
	char		*in;
	t_token		*tokens;
	t_matrix	*matrix;
	t_env		*envp;
	char		*path;
	char		*cmd_path1;
	char		*cmd_path2;
	int			last_funct;
	int			last_return;
}	t_general;

/* utilities */
void		reset(t_general *gen);
void		free_all(t_general *gen);
void		erase_temp(void);
/* format checks */
int			check_variable(char *var);
int			check_variable_char(char c);
int			check_arg_char(char c);
/* string operations */
int			check_arg_end(char *in);
char		*append_space(char *in, char *str, int to);
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
/* helper */
void		print_all_token(t_token *lst);
void		print_all_matrix(t_matrix *lst);
void		print_execute(t_execute lst);
char		*get_next_line(int fd);
/* echo */
void		ft_echo(char **it);
/* cd */
void		ft_cd(char **it);
/* pwd */
char		*ft_pwd(char *buff);
/* env */
int			copy_envp(char **envp, t_general *gen);
int			count_envp(t_env *envp);
char		*extract_env_content(char *str);
char		*extract_env_name(char *str);
void		ft_env(t_env *envp);
char		*ft_getenv(t_env *envp, char *search);
t_env		*find_env(t_env *envp, char *search);
/* export */
void		ft_export(char **it, t_env **envp);
int			ft_export_replace_exe(t_env **envp, char *add, char *name);
/* unset */
void		ft_unset(char **it, t_env **envp);
/* parse_function */
int			parse_function(t_general *gen);
void		check_quote(t_general *gen);

/* CHECKER FUNCTION */
void		check_cmd(t_token **inpt, int flag);
int			check_format(t_token *in);
int			cmd_searchlst(char *content);
int			cmd_check_contained(t_token *head);
/* linked list env */
void		env_add_back(t_env **lst, t_env *new);
void		env_add_front(t_env **lst, t_env *new);
void		env_clear(t_env **lst, void (*del)(void *));
void		env_delone(t_env *lst, void (*del)(void *));
t_env		*env_last(t_env *lst);
t_env		*env_new(char *name, char *content);
void		env_find(t_general *gen, char *search);
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
/* signals */
void		set_listeners(void);
/* error handling */
int			handle_error(int error, t_general *gen);
int			error_extract_var(t_general *gen);

/* find path */
int			find_path(t_general *gen, t_execute temp);
int			check_valid_path(t_general *gen, char *content);	
char		*find_path_str(char *name);
void		free_paths(char **paths);
void		path_arg1(char **paths, t_execute temp, t_general *gen);
void		path_arg2(char **paths, t_execute temp, t_general *gen);
/* execute */
int			execute_cases(t_general *gen);
/* pipe */
int			count_pipes(t_matrix *matrix);
void		exe_cmd(t_matrix *matrix, int pipe_count, t_env **envp);
void		execute(char **arg, t_env *envp);
int			redirect_right(t_matrix *matrix);
void		exe_pipe(t_matrix *matrix, int pipe_count, int *pipefds, int j, t_env *envp);
void		exe_heredoc(t_matrix *matrix, int pipe_count, int *pipefds, t_env *envp);
void		looping_files(t_matrix *matrix, t_env *envp);
void		looping_files2(t_matrix *matrix, t_env *envp);
void		looping_files3(t_matrix *matrix);




#endif
