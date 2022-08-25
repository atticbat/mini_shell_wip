/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:05:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/25 16:46:53 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  extract_token(char *in, t_token **head, t_general *gen)
{
    if (ft_strchr(TOKENS, in[gen->to]))
    {
        if (in[gen->to + 1] == in[gen->to])
        {
            if (in[gen->to] == '<')
                token_add_back(head, token_new('-', NULL));
            if (in[gen->to] == '>')
                token_add_back(head, token_new('+', NULL));
            gen->to++;
        }
        else
            token_add_back(head, token_new(in[gen->to], NULL));
        if (!ft_strchr(WHITESPACE, in[gen->to]))
            gen->flag = 0;
        gen->to++;
        gen->from = gen->to;
    }
    return (0);
}

static int  extract_quote(char *in, t_token **head, t_general *gen)
{
    int start;

    if (ft_strchr(QUOTES, in[gen->to]))
    {
        // if quotes is folowed by quotes and nothing else is an error
        start = gen->to;
        gen->to++;
        // printf("to: %d\n", gen->to);
        while (in[gen->to] != '\0')
        {
            if (in[gen->to] == in[start])
            {
                if (in[start] == '\'')
                    token_add_back(head, token_new('a', \
                        ft_substr(in, start + 1, gen->to - start - 1)));
                else if (in[start] == '\"')
                    token_add_back(head, token_new('d', \
                        ft_substr(in, start + 1, gen->to - start - 1)));
                gen->to++;
                break ;
            }
            gen->to++;
        }
        gen->from = gen->to;
        gen->flag = 0;
    }
    return(0);
}

static int  extract_variable(char *in, t_token **head, t_general *gen)
{
	int bracket_flag;
    int start;
	
	bracket_flag = 0;
    if (in[gen->to] == '$')
    {
        gen->to++;
        // if (ft_strchr(WHITESPACE, in[gen->to]))
    	//     token_add_back(head, token_new('a', ft_substr(in, 0, 1)));
    	if (in[gen->to] == '{')
    	{
    	    bracket_flag = 1;
    	    gen->to++;
    	}
        start = gen->to;
    	if (ft_strchr(TOKENS, in[gen->to]))
        {
    	    gen->error_no = -1;
            return (gen->error_no);
        }
    	// solve error case: $+token (show error msg "parse error near '\n'")  || ft_strchr(TOKENS, in[i + 1])
    	while (in[gen->to] != '\0')
    	{
    	    if (in[gen->to + 1] == '}' && bracket_flag)
    	    {
    	        token_add_back(head, token_new('$', ft_substr(in, start, gen->to - start + 1)));
    	        gen->to += 2;
    	        break ;
    	    }
    
    	    if (ft_strchr(TOKENS, in[gen->to + 1]) || ft_strchr(WHITESPACE, in[gen->to + 1]) \
                || in[gen->to + 1] == '\0' || in[gen->to + 1] == '$')
    	    {
    	        token_add_back(head, token_new('$', ft_substr(in, start, gen->to - start + 1)));
    	        gen->to++;
    	        break ;
    	    }
    	    gen->to++;
    	}
        gen->from = gen->to;
        // gen->flag = 1;
    }
	return (0);
}

static int  extract_argument(char *in, t_token **head, t_general *gen)
{
    if ((ft_strchr(WHITESPACE, in[gen->to]) || ft_strchr(TOKENS, in[gen->to]) \
        || ft_strchr(QUOTES, in[gen->to]) || in[gen->to] == '$') && !gen->flag && gen->to != gen->from)
    {
        token_add_back(head, token_new('a', ft_substr(in, gen->from, gen->to - gen->from)));
        if (in[gen->from] == '-' && in[gen->to] != ' ')
            token_add_back(head, token_new('a', ft_strdup(" ")));
        gen->from = gen->to;
        gen->flag = 1;
    }
    return (0);
}

static void cycle_whitespace(char *in, t_token **head, t_general *gen)
{
    if ((ft_strchr(WHITESPACE, in[gen->to])) && gen->flag)
    {
        gen->to++;
        gen->from = gen->to;
        if (!ft_strchr(WHITESPACE, in[gen->to]) && !ft_strchr(TOKENS, in[gen->to]) && in[gen->to] != '\0')
        {
            token_add_back(head, token_new('a', ft_strdup(" ")));
            gen->flag = 0;
        }
    }
    else
        gen->to++;
}

static int  get_token(char *in, t_general *gen, t_token **head)
{
    while (in[gen->to] != '\0')
    {
        //v new structure to the extracts: return success or failure, I can put flag, from, to into t_general
        if (extract_quote(in, head, gen))
            return (gen->error_no);
        else if (extract_variable(in, head, gen))
            return (gen->error_no);
        else if (extract_token(in, head, gen))
            return (gen->error_no);
        else if (extract_argument(in, head, gen))
            return (gen->error_no);
        else
            cycle_whitespace(in, head, gen);
        //^ cycle just for continue finding arg
    }
    // if (gen->to != gen->from)
    // {
    //     while (ft_strchr(WHITESPACE, in[gen->from]))
    //         gen->from++;
    //     token_add_back(head, token_new('a', ft_substr(in, gen->from, gen->to - gen->from)));
    //     if (in[gen->from] == '-' && in[gen->to + 1] != ' ')
    //         token_add_back(head, token_new('a', ft_strdup(" ")));
    // }
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
