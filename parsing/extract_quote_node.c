/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quote_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:14:44 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/17 01:02:51 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quote(t_general *gen, int (*f)(char))
{
	if ((*f)(gen->in[gen->to + 1]))
	{
		gen->to++;
		gen->flag = 0;
	}
	else
		gen->flag = 1;
}

static void	check_quote1(t_general *gen, int start)
{
	if (gen->in[start] == '\'')
		token_add_back(&gen->tokens, token_new('s', \
			append_space(gen->in, ft_substr(gen->in, \
			start + 1, gen->to - start - 1), gen->to)));
	else if (gen->in[start] == '\"')
		token_add_back(&gen->tokens, token_new('d', \
			append_space(gen->in, ft_substr(gen->in, \
			start + 1, gen->to - start - 1), gen->to)));
}

int	extract_quote_node(t_general *gen)
{
	int	start;

	if (gen->in[gen->to] != '\0' && ft_strchr(QUOTES, gen->in[gen->to]))
	{
		start = gen->to;
		gen->to++;
		while (gen->in[gen->to] != '\0')
		{
			if (gen->in[gen->to] == gen->in[start])
			{
				check_quote1(gen, start);
				break ;
			}
			gen->to++;
		}
		check_quote(gen, check_variable_char);
		gen->from = gen->to;
	}
	return (0);
}
