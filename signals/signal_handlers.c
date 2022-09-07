/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:21:33 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/07 18:11:36 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void interrupt_handler(int signum)
{
    (void) signum;
    write (1, "\n", 1);
    rl_free_line_state();
    rl_on_new_line();
	rl_replace_line("", 0);
    rl_redisplay();
}

static void	do_nothing_handler(int signum)
{
	(void) signum;
	rl_free_line_state();
    rl_on_new_line();
    rl_redisplay();
}

// static void exit_handler(int signum)
// {
//     (void) signum;
//     write(2, "exit via writing exit xdd\n", 26);
//     exit (0);
// }

void    set_listeners(void)
{
    signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, do_nothing_handler);
    // signal(SIGUSR1, exit_handler);
}