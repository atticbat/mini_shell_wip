/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:18:57 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/07 16:49:03 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset(t_general *gen)
{
	gen->last_return = gen->error_no;
    gen->error_no = 0;
    gen->to = 0;
    gen->from = 0;
    gen->flag = 0;
    if (gen->tokens)
        token_clear(&gen->tokens, free);
    if (gen->matrix)
        matrix_clear(&gen->matrix, free);
	if (gen->in)
		free (gen->in);
    gen->tokens = NULL;
    gen->matrix = NULL;
    gen->in = NULL;
}

void	free_all(t_general *gen)
{
	reset(gen);
	env_clear(&gen->envp, free);
    if (gen->path)
        free (gen->path);
}
