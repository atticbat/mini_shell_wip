/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:23:10 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/24 12:17:06 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void interrupt_handler(int signum)
{
    (void) signum;
    write (1, "\n", 1);
    rl_free_line_state();
    rl_on_new_line();
    // rl_replace_line("", 0);
    write (1, PROMPT, ft_strlen(PROMPT));
    rl_redisplay();
}

int main (int argc, char **argv, char **envp)
{
	t_token		*head;
    char		*inpt;
	t_general	gen; // no using

	(void) argc;
	(void) argv;
	(void) envp;
	head = NULL;
	inpt = NULL;
	reset(&gen, &head, inpt);
    signal(SIGINT, interrupt_handler);
    while (1)
    {
		inpt = readline(PROMPT);
		if (!inpt || !*inpt)
		    continue ;
		add_history(inpt);
		if (find_token(&gen, &head, inpt))
		{
			reset(&gen, &head, inpt);
		    continue ;
		}
		if (expand_variable(&head))
		{
			reset(&gen, &head, inpt);
			continue ;
		}
		parse_function(&head, &gen);
		reset(&gen, &head, inpt);
    }
    return (0);
}
