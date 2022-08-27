/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:50 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/28 01:42:12 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int extract_token_node(char *in, t_token **head, t_general *gen)
{
    if (in[gen->to] != '\0' && ft_strchr(TOKENS, in[gen->to]))
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
        if (!ft_strchr(TOKENS, in[gen->to + 1]))
        {
            gen->flag = 0;
            gen->to++;
        }
        else
            gen->flag = 1;
        gen->from = gen->to;
    }
    return (0);
}