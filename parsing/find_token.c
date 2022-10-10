/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:05:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/09 22:52:17 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cycle_whitespace(t_general *gen)
{
	if ((gen->in[gen->to] != '\0' && ft_strchr(WHITESPACE, gen->in[gen->to])))
	{
		gen->to++;
		gen->from = gen->to;
		if (gen->in[gen->to] != '\0' && check_arg_char(gen->in[gen->to]))
			gen->flag = 0;
	}
	else if (gen->in[gen->to] != '\0' && gen->in[gen->to] != '\\')
		gen->to++;
}

static int	extract_escaped_chars(t_general *gen)
{
	char	new_char[2];
	int		flag;

	flag = 0;
	if (gen->in[gen->to] == '\\')
	{
		if (gen->in[gen->to + 1] != '\0' \
			&& !ft_strchr(WHITESPACE, gen->in[gen->to + 1]))
		{
			gen->to++;
			new_char[0] = gen->in[gen->to];
			new_char[1] = '\0';
			token_add_back(&gen->tokens, token_new('a', ft_strdup(new_char)));
			flag = 1;
		}
		gen->to++;
		gen->from = gen->to;
		if (gen->in[gen->to] != '\0' && check_arg_char(gen->in[gen->to]))
			gen->flag = 0;
	}
	if (check_arg_end(gen->in + gen->to) && flag)
		token_add_back(&gen->tokens, token_new('a', ft_strdup(" ")));
	return (0);
}

static int	get_token(t_general *gen)
{
	while (gen->in[gen->to] != '\0')
	{
		if (extract_arg_node(gen))
			return (gen->error_no);
		else if (extract_escaped_chars(gen))
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

int	find_token(t_general *gen)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = gen->in;
	while (ft_strchr(WHITESPACE, gen->in[i]))
		i++;
	gen->in += i;
	if (get_token(gen))
	{
		free (buffer);
		return (gen->error_no);
	}
	free (buffer);
	gen->in = NULL;
	return (0);
}
