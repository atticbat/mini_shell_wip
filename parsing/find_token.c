/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:05:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/24 14:55:09 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* all the combination of tokens willb e handle later */
static int  extract_token(char *in, t_token **head)
{
    int i;

    i = 0;
    if (in[i + 1] == in[i])
    {
        if (in[i] == '<')
            token_add_back(head, token_new('-', NULL));
        if (in[i] == '>')
            token_add_back(head, token_new('+', NULL));
        i++;
    }
    else
        token_add_back(head, token_new(in[i], NULL));
    return (i + 1);
}

static int  extract_quote(char *in, t_token **head)
{
    int i;

    i = 1;
    while (in[i] != '\0')
    {
        if (in[i] == in[0])
        {
            if (in[0] == '\'')
                token_add_back(head, token_new('a', ft_substr(in, 1, i - 1)));
            else if (in[0] == '\"')
                token_add_back(head, token_new('d', ft_substr(in, 1, i - 1)));
            i++;
            break ;
        }
        i++;
    }
    return(i);
}

static int  extract_variable(char *in, t_token **head, t_general *gen)
{
	int i;
	int bracket_flag;
	
	i = 1;
	bracket_flag = 0;
	// hadling error of only $
	if (ft_strchr(WHITESPACE, in[i]))
	{
	    token_add_back(head, token_new('a', ft_substr(in, 0, 1)));
	    return (i);
	}
	if (in[i] == '{')
	{
	    bracket_flag = 1;
	    i++;
    }
	if (ft_strchr(TOKENS, in[i])) // HAUSAUFGABE : alex
	{
	    // error msg
	    // printf("parse error near '\n'");
	    // strerror(4);
	    // exit(1);
	    gen->error_no = -1;
	    return (0);
	}
    if (!(check_variable(in + i)))
    {
        gen->error_no = -1;
	    return (0);
    }
	// solve error case: $+token (show error msg "parse error near '\n'")  || ft_strchr(TOKENS, in[i + 1])
	while (in[i] != '\0')
	{
	    if (in[i + 1] == '}' && bracket_flag)
	    {
	        token_add_back(head, token_new('$', ft_substr(in, 2, i - 1)));
	        i += 2;
	        break ;
	    }
	
	    if (ft_strchr(TOKENS, in[i + 1]) || ft_strchr(WHITESPACE, in[i + 1]) \
            || in[i + 1] == '\0' || in[i + 1] == '$')
	    {
	        token_add_back(head, token_new('$', ft_substr(in, 1, i)));
	        i++;
	        break ;
	    }
	    i++;
	}
	return(i);
}

static int  get_token(char *in, t_general *gen, t_token **head)
{
    int i;
    int j;
    int flag;

    (void) gen;
    i = 0;
    j = 0;
    flag = 0;
    while (in[i] != '\0')
    {
        // printf("char at index j: %c\n", in[j]);
        //finding conditions only for var without flags
        if ((ft_strchr(WHITESPACE, in[i]) || ft_strchr(TOKENS, in[i]) \
            || ft_strchr(QUOTES, in[i]) || in[i] == '$') && !flag && i != j)
        {
            token_add_back(head, token_new('a', ft_substr(in, j, i - j)));
            j = i;
            flag = 1;
            continue ;
        }
        if (in[i] == '$')
        {
            i += extract_variable(in + i, head, gen);
            if (gen->error_no) 
            {
                write (2, "parse error: invalid variable name\n", 35);
                return (gen->error_no);
            }
            j = i;
            flag = 1;
            continue ;
        }
        if (ft_strchr(QUOTES, in[i]))
        {
            // if quotes is folowed by quotes and nothing else is an error
            i += extract_quote(in + i, head);
            j = i;
            continue ;
        }
        if (ft_strchr(TOKENS, in[i]))
        {
            i += extract_token(in + i, head);
            if (!ft_strchr(WHITESPACE, in[i]))
                flag = 0;
            j = i;
            continue ;
        }
        //cycle just for continue finding arg
        if ((ft_strchr(WHITESPACE, in[i])) && flag)
        {
            i++;
            j = i;
            if (!ft_strchr(WHITESPACE, in[i]) && !ft_strchr(TOKENS, in[i]))
            {
                token_add_back(head, token_new('a', ft_strdup(" ")));
                flag = 0;
            }
            continue ;
        }
        i++;
    }
    if (i != j)
    {
        while (ft_strchr(WHITESPACE, in[j]))
            j++;
        token_add_back(head, token_new('a', ft_substr(in, j, i - j)));
    }
    return (0);
}

int 	find_token(t_general *gen, t_token **head, char *inpt)
{
	int i;

	i = 0;
	while (ft_strchr(WHITESPACE, inpt[i])) // find space before till find
		i++;
	inpt += i; //input is moved till find the variable
	if (get_token(inpt, gen, head) != 0)
		return (gen->error_no);
	print_all(*head);
//	reset(gen, head);
	return (0);
}
