/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:23:30 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/25 11:03:06 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
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

typedef struct  s_general
{
    int     error_no;
    char    *str;
}   t_general;

/* utilities */
void	reset(t_general *gen, t_token **head, char *inpt);
/* initial parsing */
int 	find_token(t_general *gen, t_token **head, char *inpt);
/* linked list */
void	token_add_back(t_token **lst, t_token *new);
void	token_add_front(t_token **lst, t_token *new);
void	token_clear(t_token **lst, void (*del)(void *));
void	token_delone(t_token *lst, void (*del)(void *));
t_token	*token_last(t_token *lst);
t_token	*token_new(char type, char *content);
int	    token_size(t_token *lst);
/* variable expansion */ 
int		expand_variable(t_token **head);
/* helper */
void    print_all(t_token *lst);
/* echo */
char    *ft_echo(t_token **head);
/* pwd */
char	*ft_pwd(char *buff);
/* parse_function */
int		parse_function(t_token **head, t_general *gen);
/* CHECKER FUNCTION */
void		check_cmd(t_token **inpt,int flag);
int		check_variable(char *var);
int    token_searchlst(t_token *head);



#endif
