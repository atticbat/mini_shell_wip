/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quote_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:14:44 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/18 16:17:54 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	toggle_arg(t_general *gen, int (*f)(char))
{
	if ((*f)(gen->in[gen->to + 1]))
	{
		gen->to++;
		gen->flag = 0;
	}
	else
	{
		printf("export : not a valid command identifier \n");
		gen->flag = 1;
	}
}

static void	check_quote(t_general *gen, int start, char *final)
{
	if (gen->in[start] == '\'')
		token_add_back(&gen->tokens, token_new('s', \
			append_space(gen->in, ft_substr(gen->in, \
			start + 1, gen->to - start - 1), gen->to)));
	else if (gen->in[start] == '\"')
		token_add_back(&gen->tokens, token_new('d', \
			append_space(gen->in, final, gen->to)));
}

static char	*extract_escaped(t_general *gen, char *str)
{
	char	*final;
	char	buffer[2];

	final = NULL;
	gen->to++;
	final = ft_strjoinfree(str, ft_substr(gen->in, gen->from, \
		gen->to - gen->from - 1));
	buffer[0] = gen->in[gen->to];
	buffer[1] = '\0';
	final = ft_strjoinfree(final, ft_strdup(buffer));
	gen->to++;
	gen->from = gen->to;
	return (final);
}

int	extract_quote_node(t_general *gen)
{
	int		start;
	char	*final;

	final = ft_strdup("");
	if (gen->in[gen->to] != '\0' && ft_strchr(QUOTES, gen->in[gen->to]))
	{
		start = gen->to;
		gen->to++;
		gen->from = gen->to;
		while (gen->in[gen->to] != '\0')
		{
			if (gen->in[gen->to] == '\\' && (gen->in[gen->to + 1] == '\\' \
				|| (gen->in[gen->to + 1] == '\"')))
				final = extract_escaped(gen, final);
			else
				gen->to++;
			if (gen->in[gen->to] == gen->in[start])
			{
				final = ft_strjoinfree(final, ft_substr(gen->in, gen->from, \
					gen->to - gen->from));
				check_quote(gen, start, final);
				break ;
			}
		}
		toggle_arg(gen, check_variable_char);
		gen->from = gen->to;
	}
	return (0);
}
