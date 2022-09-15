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
int	g_flag = 0;

static void interrupt_handler_input(int signum)
{
    (void) signum;
    write (1, "\n", 1);
    rl_free_line_state();
    rl_on_new_line();
	rl_replace_line("", 0);
    rl_redisplay();
}

static void interrupt_handler_heredoc(int signum)
{
    (void) signum;
	write (0, "\0", 1);
	g_flag = EXIT_HEREDOC;
}

static void	do_nothing_handler(int signum)
{
	(void) signum;
	rl_free_line_state();
    rl_on_new_line();
    rl_redisplay();
}

void	toggle_interrupt_listener(void)
{
	static int	toggle = -1;

	if (toggle > 0)
		signal(SIGINT, interrupt_handler_input);
	else
		signal(SIGINT, interrupt_handler_heredoc);
	toggle *= -1;
}

void    set_listeners(void)
{
	signal(SIGINT, interrupt_handler_input);
	signal(SIGQUIT, do_nothing_handler);
}
