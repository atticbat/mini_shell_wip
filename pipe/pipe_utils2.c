/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:48:47 by aparedes          #+#    #+#             */
/*   Updated: 2022/10/04 06:08:33 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_tokens(t_matrix **matrix, t_execute *exevars)
{
	(void) exevars;
	if ((*matrix)->operator == '|')
	{
		*matrix = (*matrix)->next;
		return (1);
	}
	else if ((*matrix)->operator == '>' || (*matrix)->operator == '+' \
		|| (*matrix)->operator == '<' || (*matrix)->operator == '-')
	{
		*matrix = (*matrix)->next;
		if (*matrix)
			*matrix = (*matrix)->next;
		return (1);
	}
	return (0);
}

static void	execute_children(t_matrix **it, t_execute *exevars, t_env *envp)
{
	pid_t	pid;
	int		status;

	pipe(exevars->pipeA);
	pid = fork();
	if (pid == -1)
		exit (FAILFORK_ERR);
	else if (pid == 0)
	{
		close(exevars->pipeA[READ_END]);
		if (count_operators(*it, "|"))
			dup2(exevars->pipeA[WRITE_END], WRITE_END);
		redirect(it, exevars);
		execute((*it)->matrix, envp);
	}
	else
	{
		close(exevars->pipeA[WRITE_END]);
		dup2(exevars->pipeA[READ_END], READ_END);
		wait(&status);
	}
}

static int	create_child(t_matrix *matrix, t_execute *exevars, t_env *envp)
{
	pid_t		pid;
	t_matrix	*it;
	int	ret_value;

	it = matrix;
	ret_value = 0;
	pid = fork();
	if (pid == -1)
		exit (FAILFORK_ERR);
	else if (pid == 0)
	{
		while (it)
		{
			if (skip_tokens(&it, exevars))
				continue ;
			if (it->next && it->next->operator == '-')
				exevars->heredoc_n++;
			execute_children(&it, exevars, envp);
			exevars->last_arg = it->matrix[0];
			it = it->next;
		}
		exit(0);
	}
	else
		waitpid(pid, &ret_value, exevars->status);
	set_listeners();
	return (ret_value);
}

int	exe_cmd(t_matrix *matrix, t_execute *exevars, t_env **envp)
{
	t_matrix	*it;
	int	heredoc_n;

	it = matrix;
	heredoc_n = 0;
	signal(SIGINT, SIG_IGN);
	while (it)
	{
		if (it->operator == '-')
		{
			heredoc_n++;
			exe_heredoc(it, exevars, *envp, heredoc_n);
		}
		it = it->next;
	}
	return (create_child(matrix, exevars, *envp));
}
