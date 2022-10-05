/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:48:47 by aparedes          #+#    #+#             */
/*   Updated: 2022/10/06 01:05:11 by khatlas          ###   ########.fr       */
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
		dup2(exevars->saved_stdout, WRITE_END);
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

static int	execute_children(t_matrix *it, t_execute *exevars, t_env *envp)
{
	pid_t	pid;
	int		ret_value;

	ret_value = 0;
	pipe(exevars->pipe);
	pid = fork();
	if (pid == -1)
		exit (FAILFORK_ERR);
	else if (pid == 0)
	{
		close(exevars->pipe[READ_END]);
		if (it->next && it->next->operator == '|')
			dup2(exevars->pipe[WRITE_END], WRITE_END);
		execute(it->matrix, envp);
	}
	else
	{
		close(exevars->pipe[WRITE_END]);
		dup2(exevars->pipe[READ_END], READ_END);
		waitpid(pid, &ret_value, 0);
	}
	return (ret_value);
}

static void	child_process(t_matrix *matrix, t_execute *exevars, t_env *envp)
{
	t_matrix	*it;
	t_matrix	*buffer;

	it = matrix;
	buffer = it;
	exevars->saved_stdout = dup(1);
	pipe(exevars->pipe);
	while (it)
	{
		if (skip_tokens(&it, exevars, &buffer))
			continue ;
		if (redirect(&it, exevars))
			continue ;
		else
			execute_children(buffer, exevars, envp);
		exevars->last_arg = it->matrix[0];
		it = it->next;
	}
	close (exevars->saved_stdout);
}

static int	create_child(t_matrix *matrix, t_execute *exevars, t_env *envp)
{
	pid_t		pid;
	int			ret_value;

	ret_value = 0;
	pid = fork();
	if (pid == -1)
		exit (FAILFORK_ERR);
	else if (pid == 0)
	{
		child_process(matrix, exevars, envp);
		exit(1);
	}
	else
		waitpid(pid, &ret_value, 0);
	set_listeners();
	if (ret_value != 0)
		ret_value = 1;
	return (ret_value);
}

int	exe_cmd(t_matrix *matrix, t_execute *exevars, t_env **envp)
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
			exe_heredoc(it, exevars, *envp, heredoc_n);
		}
		it = it->next;
	}
	return (create_child(matrix, exevars, *envp));
}
