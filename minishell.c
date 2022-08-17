/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:23:10 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/17 12:40:32 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (void)
{
	t_token		*head;
    char		*inpt;
	t_general	gen;

	head = NULL;
	reset(&gen, &head);
    while (1)
    {
        inpt = readline(PROMPT);
        add_history(inpt);
		parse_token(&gen, &head, inpt);
		free (inpt);
    }
    return (0);
}