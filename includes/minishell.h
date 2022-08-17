/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:23:30 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/17 15:03:18 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
// # include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# define PROMPT "minishell $ "
# define WHITESPACE "\t\r\n\v "
# define QUOTES "\"\'"
# define TOKENS "<|>&"
// # define MAX_WORDS 8000

// typedef enum    e_priority { EXEC = 0, REDIR, PIPE, LIST, BACK } e_priority;

typedef struct  s_token
{
    char            type;
    char            *content;
    struct s_token  *next;
}   t_token;

typedef struct  s_general
{
    int     j;
}   t_general;

/* initial parsing */
// void	init(t_general *gen);
void	reset(t_general *gen, t_token **head);
void	parse_token(t_general *gen, t_token **head, char *inpt);
/* linked list */
void	token_add_back(t_token **lst, t_token *new);
void	token_add_front(t_token **lst, t_token *new);
void	token_clear(t_token **lst, void (*del)(void *));
void	token_delone(t_token *lst, void (*del)(void *));
t_token	*token_last(t_token *lst);
t_token	*token_new(char type, char *content);
int	    token_size(t_token *lst);
/* helper */
void    print_all(t_token *lst);

#endif