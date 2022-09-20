/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:48:47 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/20 20:28:12 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_alone(t_matrix **matrix, t_execute *exevars, t_env *envp)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork ();
	if (pid == 0)
	{
		signal(SIGINT, interrupt_handler_child);
		exe_heredoc(*matrix, exevars, envp);
		while (i < 2 * exevars->pipe_count)
		{
			close(exevars->pipefds[i]);
			i++;
		}
		kill(getppid(), SIGCONT);
		exit (0);
	}
	rl_replace_line("", 0);
	*matrix = (*matrix)->next;
	if (*matrix)
		*matrix = (*matrix)->next;
}

static int	skip_tokens(t_matrix **matrix, t_execute *exevars)
{
	if ((*matrix)->operator == '|')
	{
		*matrix = (*matrix)->next;
		exevars->flag = 1;
		return (1);
	}
	else if (((*matrix)->operator == '>' || (*matrix)->operator == '+' \
		|| (*matrix)->operator == '<' || (*matrix)->operator == '-') \
		&& !exevars->flag)
	{
		*matrix = (*matrix)->next;
		if (*matrix)
			*matrix = (*matrix)->next;
		return (1);
	}
	return (0);
}

static void	external_functions(t_matrix *matrix, t_env **envp)
{
	(void) envp;
	if (!matrix)
		;
	else if (matrix->operator == 'N')
		perror("Command not found");
}

static void	close_all(t_execute *exevars)
{
	int	i;

	i = 0;
	while (i < exevars->pipe_count * 2)
	{
		close (exevars->pipefds[i]);
		i++;
	}
	i = 0;
	while (i < exevars->pipe_count + 1)
	{
		wait (&(exevars->status));
		i++;
	}
	set_listeners();
}

void	exe_cmd(t_matrix *matrix, t_execute *exevars, t_env **envp)
{
	signal(SIGINT, SIG_IGN);	
	while (matrix)
	{
		if (skip_tokens(&matrix, exevars))
			continue ;
		if (exevars->flag && matrix->operator == '-')
		{
			heredoc_alone(&matrix, exevars, *envp);
			exevars->index += 2;
			exevars->flag = 0;
			continue ;
		}
		exe_pipe (matrix, exevars, *envp);
		external_functions(matrix, envp);
		if (matrix)
			matrix = matrix->next;
		exevars->index += 2;
		exevars->flag = 0;
	}
	close_all(exevars);
}
