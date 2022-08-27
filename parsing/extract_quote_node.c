/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quote_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:14:44 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/27 04:31:37 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  extract_quote_node(char *in, t_token **head, t_general *gen)
{
    int start;

    if (in[gen->to] != '\0' && ft_strchr(QUOTES, in[gen->to]))
    {
        start = gen->to;
        gen->to++;
        while (in[gen->to] != '\0')
        {
            if (in[gen->to] == in[start])
            {
                if (in[start] == '\'')
                    token_add_back(head, token_new('a', append_space(in, \
                        ft_substr(in, start + 1, gen->to - start - 1), gen->to)));
                else if (in[start] == '\"')
                    token_add_back(head, token_new('d', append_space(in, \
                        ft_substr(in, start + 1, gen->to - start - 1), gen->to)));
                break ;
            }
            gen->to++;
        }
        if(check_variable_char(in[gen->to + 1]))
        {
            gen->to++;
            gen->flag = 0;
        }
        else
            gen->flag = 1;
        gen->from = gen->to;
    }
    return(0);
}