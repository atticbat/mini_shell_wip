/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:48:47 by aparedes          #+#    #+#             */
/*   Updated: 2022/10/05 17:47:00 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_tokens(t_matrix **matrix, t_execute *exevars, t_matrix **buffer)
{
	(void) exevars;
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

static void	execute_children(t_matrix *it, t_execute *exevars, t_env *envp)
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
		if (it->next && it->next->operator == '|')
			dup2(exevars->pipeA[WRITE_END], WRITE_END);
		execute(it->matrix, envp);
	}
	else
	{
		close(exevars->pipeA[WRITE_END]);
		dup2(exevars->pipeA[READ_END], READ_END);
		wait(&status);
	}
}

// static void	filename_args(t_matrix *matrix)
// {
// 	int	i;
// 	int	fd;
// 	t_matrix *it;

// 	it = matrix;
// 	i = 1;
// 	if (!it)
// 		return ;
// 	fd = open (it->matrix[0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
// 	dup2(fd, WRITE_END);
// 	while (it->matrix[i])
// 	{
// 		if (check_file(it->matrix[i]))
// 			perror(it->matrix[i]);
// 		else
// 		{
// 			write (WRITE_END, it->matrix[i], ft_strlen(it->matrix[i]));
// 			write (WRITE_END, "\n", 1);
// 		}
// 		i++;
// 	}
// 	close (fd);
// }

static int	create_child(t_matrix *matrix, t_execute *exevars, t_env *envp)
{
	pid_t		pid;
	t_matrix	*it;
	int	ret_value;
	t_matrix	*buffer;

	it = matrix;
	ret_value = 0;
	pid = fork();
	buffer = NULL;
	if (pid == -1)
		exit (FAILFORK_ERR);
	else if (pid == 0)
	{
		buffer = it;
		exevars->saved_stdout = dup(1);
		while (it)
		{
			if (skip_tokens(&it, exevars, &buffer))
				continue ;
 			if (redirect(&it, exevars))
				continue ;
			else
				execute_children(buffer, exevars, envp);
			exevars->last_arg = it->matrix[0];
			// if ((!it->next || it->next->operator == '|') && buffer->next \
			// 	&& buffer->next->next && buffer != it)
			// 	filename_args(buffer->next->next);
			it = it->next;
		}
		close (exevars->saved_stdout);
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
