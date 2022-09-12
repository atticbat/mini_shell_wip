/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:11:43 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/12 15:44:33 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_function(t_general *gen)
{
	t_token	*it;
	char	*buffer;

	buffer = NULL;
	if (!gen->tokens)
		return (-1);
	it = gen->tokens;
	if (!check_format(it))
	{
		gen->error_no = -1;
		return (gen->error_no);
	}
	create_matrix(&it, gen);
	print_all_matrix(gen->matrix);
	return (0);
}
