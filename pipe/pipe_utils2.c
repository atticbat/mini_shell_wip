/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:48:47 by aparedes          #+#    #+#             */
/*   Updated: 2022/10/10 04:32:52 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_tokens(t_matrix **matrix, t_execute *exevars, \
	t_matrix **buffer)
{
	if ((*matrix)->operator == '|')
	{
		*matrix = (*matrix)->next;
		*buffer = *matrix;
		if (!find_pipes(*matrix))
			dup2(exevars->saved_stdout, WRITE_END);
		exevars->current_pipe--;
		return (1);
	}
	else if ((*matrix)->operator == '>' || (*matrix)->operator == '+' \
		|| (*matrix)->operator == '<' || (*matrix)->operator == '-')
	{
		*matrix = (*matrix)->next;
		return (1);
	}
	return (0);
}

static void	execute_children(t_matrix *it, t_execute *exevars, t_env *envp)
{
	if (pipe(exevars->pipe))
		exit (1);
	exevars->pids[exevars->current_pipe] = fork();
	if (exevars->pids[exevars->current_pipe] == -1)
		exit (FAILFORK_ERR);
	else if (exevars->pids[exevars->current_pipe] == 0)
	{
		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		close(exevars->pipe[READ_END]);
		if (it->next && it->next->operator == '|')
			dup2(exevars->pipe[WRITE_END], WRITE_END);
		execute(it->matrix, envp);
	}
	else
	{
		close(exevars->pipe[WRITE_END]);
		dup2(exevars->pipe[READ_END], READ_END);
		close (exevars->pipe[READ_END]);
	}
}

static int	child_process(t_matrix *matrix, t_execute *exevars, t_env *envp)
{
	t_matrix	*it;
	t_matrix	*buffer;
	int			ret_value;

	ret_value = 0;
	it = matrix;
	buffer = it;
	exevars->saved_stdout = dup(1);
	while (it)
	{
		if (skip_tokens(&it, exevars, &buffer))
			continue ;
		if (redirect(&it, exevars))
			continue ;
		execute_children(buffer, exevars, envp);
		exevars->last_arg = it->matrix[0];
		it = it->next;
	}
	while (exevars->pipe_count >= 0)
	{
		waitpid(exevars->pids[exevars->pipe_count], &ret_value, 0);
		exevars->pipe_count--;
	}
	close (exevars->saved_stdout);
	return (ret_value / 256);
}

static void	create_child(t_matrix *matrix, t_execute *exevars, t_general *gen)
{
	pid_t		pid;
	int			ret_value;

	ret_value = 0;
	pid = fork();
	if (pid == -1)
		exit (FAILFORK_ERR);
	else if (pid == 0)
	{
		ret_value = child_process(matrix, exevars, gen->envp);
		if (ret_value)
			exit(ret_value);
		exit(gen->error_no);
	}
	else
		waitpid(pid, &ret_value, 0);
	gen->error_no = (ret_value / 256);
}

void	exe_cmd(t_matrix *matrix, t_execute *exevars, t_general *gen)
{
	t_matrix	*it;
	int			heredoc_n;

	it = matrix;
	heredoc_n = 0;
	signal(SIGINT, SIG_IGN);
	while (it)
	{
		if (it->operator == '-')
		{
			heredoc_n++;
			exe_heredoc(it, exevars, gen->envp, heredoc_n);
		}
		it = it->next;
	}
	create_child(matrix, exevars, gen);
	set_listeners();
}
