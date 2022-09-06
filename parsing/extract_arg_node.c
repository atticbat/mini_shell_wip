/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_arg_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:19:32 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/06 21:13:01 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  adjust_cmd(t_general *gen)
{
    t_token *buffer;
    int     len;

    buffer = token_last(gen->tokens);
    len = ft_strlen(buffer->content);
    if (!buffer || !buffer->content)
    {
        gen->error_no = -1;
        return (gen->error_no);
    }
    if (cmd_check_contained(buffer) && buffer->content[len - 1] == ' ')
        buffer->content[len - 1] = '\0';
    return (0);
}

static int  ignore_whitespace_arg(char *in, int from, int to)
{
    while (from < to)
    {
        if (ft_strchr(WHITESPACE, in[from]))
            return (-1);
        from++;
    }
    return (0);
}

int  extract_arg_node(t_general *gen)
{
    if (gen->in[gen->to] != '\0' && !check_arg_char(gen->in[gen->to]) \
        && !gen->flag && gen->to != gen->from \
        && !ignore_whitespace_arg(gen->in, gen->from, gen->to))
    {
        token_add_back(&gen->tokens, token_new('a', append_space(gen->in, \
            ft_substr(gen->in, gen->from, gen->to - gen->from), gen->to - 1)));
        if (check_arg_end(gen->in + gen->to))
        {
            gen->flag = 1;
            if (adjust_cmd(gen))
                return (gen->error_no);
        }
        gen->from = gen->to;
    }
    return (0);
}

int find_final_arg(t_general *gen)
{
    if (gen->to != gen->from)
    {
        while (gen->in[gen->from] != '\0' \
            && ft_strchr(WHITESPACE, gen->in[gen->from]))
        {
            gen->from++;
            gen->flag = 0;
        }
        if (gen->to != gen->from && !gen->flag)
            token_add_back(&gen->tokens, token_new('a', ft_substr(gen->in, \
                gen->from, gen->to - gen->from)));
    }
    return (0);
}
