/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:48:47 by aparedes          #+#    #+#             */
/*   Updated: 2022/10/04 04:27:57 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	heredoc_alone(t_matrix **matrix, t_execute *exevars, t_env *envp)
// {
// 	pid_t	pid;
// 	int		i;

// 	i = 0;
// 	pid = fork ();
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, interrupt_handler_child);
// 		exe_heredoc(*matrix, exevars, envp);
// 		while (i < 2 * exevars->pipe_count)
// 		{
// 			close(exevars->pipefds[i]);
// 			i++;
// 		}
// 		kill(getppid(), SIGCONT);
// 		exit (0);
// 	}
// 	rl_replace_line("", 0);
// 	*matrix = (*matrix)->next;
// 	if (*matrix)
// 		*matrix = (*matrix)->next;
// }

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

// static void	external_functions(t_matrix *matrix, t_env **envp)
// {
// 	(void) envp;
// 	if (!matrix)
// 		;
// 	else if (matrix->operator == 'N')
// 		perror("Command not found");
// }

// static void	close_all(t_execute *exevars)
// {
// 	int	i;

// 	i = 0;
// 	while (i < exevars->pipe_count * 2)
// 	{
// 		close (exevars->pipefds[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < exevars->pipe_count + 1)
// 	{
// 		wait (&(exevars->status));
// 		i++;
// 	}
// 	set_listeners();
// }
// static void	exe_pipe_test(t_matrix *matrix, t_env *envp)
// {
// 	/* empezamos haciendo el conteo de los comandos */
// 	char	*cmd_path;
// 	char	**arg;
// 	int		flag_first = 1;
// 	int		flag_last = 0;

// 	arg = matrix->matrix;
// 	cmd_path = find_path_str(arg[0]);
// 	printf("\npath %s \n", cmd_path);
// 	if(!matrix)
// 		return ;
// 	if (cmd_searchlst(arg[0]) == EXPORT_CMD && !arg[1])
// 		export_print_vars(envp);
	
// 	pid_t	pid;
// 	int		fd[2];
// 	int		i;

// 	if (pipe(fd) = -1)
// 	{
// 		perror("Pipe failed.");
// 		return ;
// 	}
// 	// check of heredoc command
// 	while(1)
// 	{
// 		pid = fork();
// 		// child
// 		if (pid == 0)
// 		{
// 			if(flag_first == 1 && flag_last == 1 )
// 			{
// 				dup2(fd[1])
// 			}
// 			if (execv(cmd_path, arg) == -1)
// 				exit (-1);
// 		}
		
// 	}

// }

static void	execute_children(t_matrix **it, t_execute *exevars, t_env *envp)
{
	pid_t	pid;
	int		status;

	pipe(exevars->pipeA);
	pid = fork();
	if (pid == -1)
		perror("child fork failed\n");
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
		perror ("Fork failed\n");
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
