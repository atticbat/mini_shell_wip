/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:18:57 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/31 12:53:42 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset(t_general *gen, t_token **head, char *inpt)
{
    if (gen->str)
        free (gen->str);
	gen->last_return = gen->error_no;
    gen->error_no = 0;
    gen->to = 0;
    gen->from = 0;
    gen->flag = 0;
    gen->str = NULL;
    if (head)
        token_clear(head, free);
    *head = NULL;
	if (inpt)
		free (inpt);
    inpt = NULL;
}

void	free_all(char *inpt, t_token **head, t_general *gen)
{
	reset(gen, head, inpt);
	env_clear(&gen->envp, free);
}
