/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:23:30 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/01 15:11:57 by khatlas          ###   ########.fr       */
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

typedef struct  s_general
{
    int     error_no;
    int     to;
    int     from;
    int     flag;
    char    *str;
    t_env   *envp;
    char    *path;
    int     last_funct;
    int     last_return;
}   t_general;

/* utilities */
void	reset(t_general *gen, t_token **head, char *inpt);
void	free_all(char *inpt, t_token **head, t_general *gen);
/* format checks */
int		check_variable(char *var);
int     check_variable_char(char c);
int     check_arg_char(char c);
/* string operations */
int     check_arg_end(char *in);
char    *append_space(char *in, char *str, int to);
/* initial parsing */
int 	find_token(char *in, t_token **head, t_general *gen);
int     extract_quote_node(char *in, t_token **head, t_general *gen);
int     extract_var_node(char *in, t_token **head, t_general *gen);
int     extract_arg_node(char *in, t_token **head, t_general *gen);
int     find_final_arg(char *in, t_token **head, t_general *gen);
int     extract_token_node(char *in, t_token **head, t_general *gen);
/* linked list token */
void	token_add_back(t_token **lst, t_token *new);
void	token_add_front(t_token **lst, t_token *new);
void	token_clear(t_token **lst, void (*del)(void *));
void	token_delone(t_token *lst, void (*del)(void *));
t_token	*token_last(t_token *lst);
t_token	*token_new(char type, char *content);
int	    token_size(t_token *lst);
/* variable expansion */ 
int	    expand_variable(t_token **head, t_general *gen);
/* helper */
void    print_all(t_token *lst);
/* echo */
void    ft_echo(t_token *it,t_general *gen,int *flag);
/* cd */
int     ft_cd(t_token *it);
/* pwd */
char	*ft_pwd(char *buff);
/* env */
int	    copy_envp(char **envp, t_general *gen);
char	*extract_env_content(char *str);
char	*extract_env_name(char *str);
int	    count_envp(t_env *envp);
char    *ft_env(t_env *envp);
char    *ft_getenv(t_env *envp, char *search);
t_env   *find_env(t_env *envp, char *search);
/* export */
void    ft_export(t_token *it, t_general *gen);
int     ft_export_replace_exe(t_env **envp, char *add, char *name);
/* unset */
int     ft_unset_exe(t_env **envp, char *name);
void    ft_unset(t_token *it, t_general *gen);
/* parse_function */
int		parse_function(t_token **head, t_general *gen);
/* CHECKER FUNCTION */
void	check_cmd(t_token **inpt,int flag);
int     check_format(t_token *in);
int     cmd_searchlst(t_token *head);
int     cmd_check_contained(t_token *head);
/* linked list env */
void	env_add_back(t_env **lst, t_env *new);
void	env_add_front(t_env **lst, t_env *new);
void	env_clear(t_env **lst, void (*del)(void *));
void	env_delone(t_env *lst, void (*del)(void *));
t_env	*env_last(t_env *lst);
t_env	*env_new(char *name, char *content);
/* signals */
void    set_listeners(void);
/* error_handling */
int	    handle_error(int error, char *inpt, t_token **head, t_general *gen);




void    env_find(t_general *gen, char *search);

#endif
