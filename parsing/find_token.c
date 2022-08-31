/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:05:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/31 08:27:10 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void cycle_whitespace(char *in, t_token **head, t_general *gen)
{
    (void)head;
    if ((in[gen->to] != '\0' && ft_strchr(WHITESPACE, in[gen->to])))
    {
        gen->to++;
        gen->from = gen->to;
        if (in[gen->to] != '\0' && check_variable_char(in[gen->to]))
            gen->flag = 0;
    }
    else if (in[gen->to] != '\0')
        gen->to++;
}

static int  get_token(char *in, t_token **head, t_general *gen)
{
    while (in[gen->to] != '\0')
    {
        if (extract_arg_node(in, head, gen))
            return (gen->error_no);
        else if (extract_token_node(in, head, gen))
            return (gen->error_no);
        else if (extract_quote_node(in, head, gen))
            return (gen->error_no);
        else if (extract_var_node(in, head, gen))
            return (gen->error_no);
        else
            cycle_whitespace(in, head, gen);
    }
    if (find_final_arg(in, head, gen))
        return (gen->error_no);
    return (0);
}

int 	find_token(char *in, t_token **head, t_general *gen)
{
	int i;

	i = 0;
	while (ft_strchr(WHITESPACE, in[i]))
		i++;
	in += i;
	if (get_token(in, head, gen) != 0)
		return (gen->error_no);
	print_all(*head);
	return (0);
}
