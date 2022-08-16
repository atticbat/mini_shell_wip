/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:23:10 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/16 16:31:18 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int main (void)
{
	t_token		*head;
    char		*inpt;
	int			i;
	t_general	gen;

	head = NULL;
	init(&gen);
	reset(&gen, &head);
    while (i <  MAX_WORDS)
    {
        inpt = readline(PROMPT);
        add_history(inpt);
		parse_token(&gen, &head, inpt);
		free (inpt);
		// reset(&gen);
        ++i;
    }
    return (0);
}