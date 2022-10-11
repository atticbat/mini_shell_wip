/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_matrix_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 04:03:49 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/11 17:59:13 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dummy_heredoc(t_token *it, t_env *envp)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		perror("failed pipe");
	else if (pid == 0)
	{
		signal(SIGINT, interrupt_handler_child);
		ft_heredoc(it->next->content, envp, 1);
		exit (0);
	}
	else
		waitpid(pid, &status, 0);
	set_listeners();
}

void	skip_multiple_ins(t_token **it, t_general *gen)
{
	while ((*it) && (*it)->next && (*it)->next->next)
	{
		if ((*it)->next->next->type == '<')
		{
			if ((*it)->next->content && check_file((*it)->next->content))
				perror((*it)->next->content);
			(*it) = (*it)->next;
			(*it) = (*it)->next;
		}
		else if ((*it)->next->next->type == '-')
		{
			dummy_heredoc(*it, gen->envp);
			(*it) = (*it)->next;
			(*it) = (*it)->next;
		}
		else
			break ;
	}
}
