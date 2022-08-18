/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:23:10 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/18 17:26:53 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (void)
{
	t_token		*head;
    char		*inpt;
	t_general	gen; // no using

	head = NULL;
	reset(&gen, &head); // reset to for the variables before start
    while (1)
    {
        inpt = readline(PROMPT); // show prompt and read line
        add_history(inpt);
		find_token(&gen, &head, inpt); //take initialized list &general var
		free (inpt);
    }
    return (0);
}