/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:21:33 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/20 06:57:18 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	interrupt_handler_input(int signum)
{
	(void) signum;
	write (1, "\n", 1);
	rl_free_line_state();
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_listeners(void)
{
	signal(SIGINT, interrupt_handler_input);
	signal(SIGQUIT, SIG_IGN);
}

void	interrupt_handler_child(int signum)
{
	(void) signum;
	write (1, "\r", 1);
	exit(0);
}
