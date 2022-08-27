/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:50 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/27 02:26:26 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int extract_token_node(char *in, t_token **head, t_general *gen)
{
    if (in[gen->to] != '\0' && ft_strchr(TOKENS, in[gen->to]))
    {
        // printf("to: %d, current char: %c\n", gen->to, in[gen->to]);
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
        else
            gen->flag = 1;
        gen->to++;
        gen->from = gen->to;
    }
    return (0);
}