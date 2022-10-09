/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:11:43 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/09 01:16:09 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_function(t_general *gen)
{
	t_token	*it;
	char	*buffer;

	buffer = NULL;
	if (!gen->tokens)
		return (1);
	it = gen->tokens;
	if (!check_format(it))
	{
		gen->error_no = SYNTAX_ERR;
		return (gen->error_no);
	}
	create_matrix(&it, gen);
	token_clear(&gen->tokens, free);
	return (0);
}
