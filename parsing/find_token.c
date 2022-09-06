/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:05:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/06 21:11:43 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void cycle_whitespace(t_general *gen)
{
    if ((gen->in[gen->to] != '\0' && ft_strchr(WHITESPACE, gen->in[gen->to])))
    {
        gen->to++;
        gen->from = gen->to;
        if (gen->in[gen->to] != '\0' && check_arg_char(gen->in[gen->to]))
            gen->flag = 0;
    }
    else if (gen->in[gen->to] != '\0')
        gen->to++;
}

static int  get_token(t_general *gen)
{
    while (gen->in[gen->to] != '\0')
    {
        if (extract_arg_node(gen))
            return (gen->error_no);
        else if (extract_token_node(gen))
            return (gen->error_no);
        else if (extract_quote_node(gen))
            return (gen->error_no);
        else if (extract_var_node(gen))
            return (gen->error_no);
        else
            cycle_whitespace(gen);
    }
    if (find_final_arg(gen))
        return (gen->error_no);
    return (0);
}

int 	find_token(t_general *gen)
{
	int i;

	i = 0;
	while (ft_strchr(WHITESPACE, gen->in[i]))
		i++;
	gen->in += i;
	if (get_token(gen))
		return (gen->error_no);
	// print_all_token(*head);
	return (0);
}
