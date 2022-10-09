/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:59:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/09 22:43:23 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_extract_var(t_general *gen)
{
	int	bracket_flag;

	bracket_flag = 0;
	if (ft_strchr(WHITESPACE, gen->in[gen->to]))
		token_add_back(&gen->tokens, token_new('a', ft_strdup("$")));
	if (gen->in[gen->to] == '{')
	{
		bracket_flag = 1;
		gen->to++;
	}
	return (bracket_flag);
}

static void	operation1(t_general *gen, int start)
{
	token_add_back(&gen->tokens, token_new('$', \
		ft_substr(gen->in, start, gen->to - start + 1)));
	if (check_arg_end(gen->in + (gen->to + 2)))
		token_add_back(&gen->tokens, \
		token_new('a', ft_strdup(" ")));
	gen->to++;
}

static void	operation2(t_general *gen, int start)
{
	if (gen->in[gen->to] == ' ')
	{
		token_add_back(&gen->tokens, token_new('a', \
			ft_substr(gen->in, start, gen->to - start + 1)));
	}
	else
		token_add_back(&gen->tokens, token_new('$', \
			ft_substr(gen->in, start, gen->to - start + 1)));
	if (check_arg_end(gen->in + (gen->to + 1)))
		token_add_back(&gen->tokens, \
		token_new('a', ft_strdup(" ")));
}

static void	loop_extract_var(t_general *gen, int start, int bracket_flag)
{
	while (gen->in[gen->to] != '\0')
	{
		if (gen->in[gen->to + 1] == '}' && bracket_flag)
		{
			operation1(gen, start);
			break ;
		}
		if (!check_variable_char(gen->in[gen->to + 1]))
		{
			operation2(gen, start);
			break ;
		}
		gen->to++;
	}
}

int	extract_var_node(t_general *gen)
{
	int	bracket_flag;
	int	start;

	bracket_flag = 0;
	if (gen->in[gen->to] != '\0' && gen->in[gen->to] == '$')
	{
		gen->to++;
		bracket_flag = check_extract_var(gen);
		start = gen->to;
		error_extract_var(gen);
		loop_extract_var(gen, start, bracket_flag);
		toggle_arg(gen, check_exception_char);
		gen->from = gen->to;
	}
	return (0);
}
