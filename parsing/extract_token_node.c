/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:22:50 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/06 21:13:56 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_token_node(t_general *gen)
{
	if (gen->in[gen->to] != '\0' && ft_strchr(TOKENS, gen->in[gen->to]))
	{
		if (gen->in[gen->to + 1] == gen->in[gen->to])
		{
			if (gen->in[gen->to] == '<')
				token_add_back(&gen->tokens, token_new('-', NULL));
			if (gen->in[gen->to] == '>')
				token_add_back(&gen->tokens, token_new('+', NULL));
			gen->to++;
		}
		else
			token_add_back(&gen->tokens, token_new(gen->in[gen->to], NULL));
		if (!ft_strchr(TOKENS, gen->in[gen->to + 1]))
		{
			gen->flag = 0;
			gen->to++;
		}
		else
			gen->flag = 1;
		gen->cmd_flag = 1;
		gen->from = gen->to;
	}
	return (0);
}
