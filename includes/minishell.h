/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:23:30 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/03 18:36:08 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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
#include <sys/stat.h>
#include <fcntl.h>
# define PROMPT "minishell $ "
# define WHITESPACE "\t\r\n\v "
# define QUOTES "\"\'"
# define TOKENS "<|>&"
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
# define PATH_FILE_2  "filein_temp"

// # define MAX_WORDS 8000
/* for pwd function */
// # define GetCurrentDir _getcwd

// typedef enum    e_priority { EXEC = 0, REDIR, PIPE, LIST, BACK } e_priority;

typedef struct  s_token
{
    char            type;
    char            *content;
    struct s_token  *next;
}   t_token;

typedef struct  s_env
{
    char            *name;
    char            *content;
    struct s_env    *next;
}   t_env;

typedef struct  s_matrix
{
    char            *cmd;
    char            **matrix;
    struct s_matrix *next;
}   t_matrix;

typedef struct  s_general
{
    int         error_no;
    int         to;
    int         from;
    int         flag;
    char        *str;
    t_env       *envp;
    char        *path;
    char        *cmd_path;
    t_matrix    *matrix;
    int         last_funct;
    int         last_return;
}   t_general;

/* utilities */
void	    reset(t_general *gen, t_token **head, char *inpt);
void	    free_all(char *inpt, t_token **head, t_general *gen);
/* format checks */
int		    check_variable(char *var);
int         check_variable_char(char c);
int         check_arg_char(char c);
/* string operations */
int         check_arg_end(char *in);
char        *append_space(char *in, char *str, int to);
/* initial parsing */
int 	    find_token(char *in, t_token **head, t_general *gen);
int         extract_quote_node(char *in, t_token **head, t_general *gen);
int         extract_var_node(char *in, t_token **head, t_general *gen);
int         extract_arg_node(char *in, t_token **head, t_general *gen);
int         find_final_arg(char *in, t_token **head, t_general *gen);
int         extract_token_node(char *in, t_token **head, t_general *gen);
/* linked list token */
void	    token_add_back(t_token **lst, t_token *new);
void	    token_add_front(t_token **lst, t_token *new);
void	    token_clear(t_token **lst, void (*del)(void *));
void	    token_delone(t_token *lst, void (*del)(void *));
t_token	    *token_last(t_token *lst);
t_token	    *token_new(char type, char *content);
int	        token_size(t_token *lst);
/* variable expansion */ 
int	        expand_variable(t_token **head, t_general *gen);
/* helper */
void        print_all_token(t_token *lst);
void        print_all_matrix(t_matrix *lst);
/* echo */
void        ft_echo(t_matrix **it, t_general *gen, int *flag);
/* cd */
int         ft_cd(t_matrix **it);
/* pwd */
char	    *ft_pwd(char *buff);
/* env */
int	        copy_envp(char **envp, t_general *gen);
char	    *extract_env_content(char *str);
char	    *extract_env_name(char *str);
int	        count_envp(t_env *envp);
char        *ft_env(t_env *envp);
char        *ft_getenv(t_env *envp, char *search);
t_env       *find_env(t_env *envp, char *search);
/* export */
void        ft_export(t_matrix **it, t_general *gen);
int         ft_export_replace_exe(t_env **envp, char *add, char *name);
/* unset */
void        ft_unset(t_matrix **it,t_general *gen);
/* parse_function */
int		    parse_function(t_token **head, t_general *gen);
/* CHECKER FUNCTION */
void	    check_cmd(t_token **inpt,int flag);
int         check_format(t_token *in);
int         cmd_searchlst(char *content);
int         cmd_check_contained(t_token *head);
/* linked list env */
void	    env_add_back(t_env **lst, t_env *new);
void	    env_add_front(t_env **lst, t_env *new);
void	    env_clear(t_env **lst, void (*del)(void *));
void	    env_delone(t_env *lst, void (*del)(void *));
t_env	    *env_last(t_env *lst);
t_env	    *env_new(char *name, char *content);
void        env_find(t_general *gen, char *search);
/* linked list env */
void	    matrix_add_back(t_matrix **lst, t_matrix *new);
void	    matrix_add_front(t_matrix **lst, t_matrix *new);
void	    matrix_clear(t_matrix **lst, void (*del)(void *));
void	    matrix_delone(t_matrix *lst, void (*del)(void *));
t_matrix	*matrix_last(t_matrix *lst);
t_matrix	*matrix_new(char *cmd, char **matrix);
/* signals */
void        set_listeners(void);
/* error handling */
int	        handle_error(int error, char *inpt, t_token **head, t_general *gen);
/* find path */
int         find_path(t_general *gen, char *content);
int         check_valid_path(t_general *gen, char *content);	

#endif
