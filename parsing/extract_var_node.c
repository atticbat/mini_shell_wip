/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:17:36 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/06 20:16:05 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  extract_var_node(t_general *gen)
{
	int bracket_flag;
    int start;
	
	bracket_flag = 0;
    if (gen->in[gen->to] != '\0' && gen->in[gen->to] == '$')
    {
        gen->to++;
        if (ft_strchr(WHITESPACE, gen->in[gen->to]))
    	    token_add_back(&gen->tokens, token_new('a', ft_strdup("$")));
    	if (gen->in[gen->to] == '{')
    	{
    	    bracket_flag = 1;
    	    gen->to++;
    	}
        start = gen->to;
    	if (ft_strchr(TOKENS, gen->in[gen->to]))
        {
    	    gen->error_no = -1;
            return (gen->error_no);
        }
    	while (gen->in[gen->to] != '\0')
    	{
    	    if (gen->in[gen->to + 1] == '}' && bracket_flag)
    	    {
    	        token_add_back(&gen->tokens, token_new('$',	\
					ft_substr(gen->in, start, gen->to - start + 1)));
				if (check_arg_end(gen->in + (gen->to + 2)))
					token_add_back(&gen->tokens, token_new('a', ft_strdup(" ")));
                gen->to++;
    	        break ;
    	    }
    	    if (!check_variable_char(gen->in[gen->to + 1]))
    	    {
    	        token_add_back(&gen->tokens, token_new('$', \
					ft_substr(gen->in, start, gen->to - start + 1)));
				if (check_arg_end(gen->in + (gen->to + 1)))
					token_add_back(&gen->tokens, token_new('a', ft_strdup(" ")));
    	        break ;
    	    }
    	    gen->to++;
    	}
        if(check_variable_char(gen->in[gen->to + 1]))
        {
            gen->to++;
            gen->flag = 0;
        }
        else
            gen->flag = 1;
        gen->from = gen->to;
    }
	return (0);
}