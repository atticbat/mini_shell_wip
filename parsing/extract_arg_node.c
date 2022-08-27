/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_arg_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:19:32 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/27 02:29:03 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  adjust_cmd(t_token **head, t_general *gen)
{
    t_token *buffer;

    buffer = token_last(*head);
    if (!buffer || !buffer->content)
    {
        gen->error_no = -1;
        return (gen->error_no);
    }
    if (cmd_check_contained(buffer) && buffer->content[ft_strlen(buffer->content) - 1] == ' ')
        buffer->content[ft_strlen(buffer->content) - 1] = '\0';
    return (0);
}

int  extract_arg_node(char *in, t_token **head, t_general *gen)
{
    if (in[gen->to] != '\0' && (ft_strchr(WHITESPACE, in[gen->to]) || ft_strchr(TOKENS, in[gen->to])  \
        || ft_strchr(QUOTES, in[gen->to]) || in[gen->to] == '$') && !gen->flag && gen->to != gen->from)
    {
        if (ft_strchr(WHITESPACE, in[gen->to]))
        {
            token_add_back(head, token_new('a', ft_substr(in, gen->from, gen->to + 1 - gen->from)));
            gen->flag = 1;
            if (adjust_cmd(head, gen))
                return (gen->error_no);
        }
        else
        {
            token_add_back(head, token_new('a', ft_substr(in, gen->from, gen->to - gen->from)));
            gen->flag = 0;
        }
        gen->from = gen->to;
    }
    return (0);
}

int find_final_arg(char *in, t_token **head, t_general *gen)
{
    if (gen->to != gen->from)
    {
        while (ft_strchr(WHITESPACE, in[gen->from]))
        {
            gen->from++;
            gen->flag = 0;
        }
        if (gen->to != gen->from && !gen->flag)
            token_add_back(head, token_new('a', ft_substr(in, gen->from, gen->to - gen->from)));
    }
    return (0);
}
