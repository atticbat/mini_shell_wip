/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:48:47 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/29 16:29:58 by khatlas          ###   ########.fr       */
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
void	exe_cmd(t_matrix *matrix, t_execute *exevars, t_env **envp)
{
	(void) exevars;
	t_matrix	*it;
	int	heredoc_n;

	it = matrix;
	heredoc_n = 0;
	//heredoc starts here
	signal(SIGINT, SIG_IGN);
	while (it)
	{
		if (it->operator == '-')
		{
			heredoc_n++;
			exe_heredoc(it, exevars, *envp, heredoc_n);
			// printf("number of heredoc : %d\n", heredoc_n);
		}
		it = it->next;
	}

	//redirection file creation
	it = matrix;
	char	*buffer;
	buffer = NULL;
	while (it)
	{
		skip_tokens(&it, exevars);
		//store last argument for the case of '<'
		if (it->operator == 'F' || it->operator == 'N')
			buffer = it->matrix[0];
		if (it->operator == '>' && it->next)
		{
			it = it->next;
			//create a new file with name of following matrix[0]
			int	fd;

			fd = open (it->matrix[0],  O_WRONLY | O_TRUNC | O_CREAT, 0777);
			close (fd);
		}
		else if (it->operator == '<')
		{
			int	fd;

			fd = open (buffer, O_WRONLY | O_TRUNC | O_CREAT, 0777);
			close (fd);
		}
		else if (it->operator == '+' && it->next)
		{
			it = it->next;
			int	fd;

			fd = open (it->matrix[0], O_WRONLY | O_CREAT, 0777);
			close (fd);		
		}
		else if ((it->operator == '>' || it->operator == '+') && (!it->next || !it->next->matrix))
			perror("Invalid redirection\n");
		it = it->next;
	}
	//redirection file creation

	//now for executions
	//if there is a redirection or a heredoc then I will set the stdout and stdin respectively as the name of the file, which should be created already
	it = matrix;
	int	fd[2];
	pid_t	pid;
	int		first;

	exevars->last_output = -1;
	first = 1;
	while (it)
	{
		if (it->operator == '|')
			it = it->next;
		if (pipe(fd) < 0)
			perror("Pipe failure.\n");
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid < 0)
			perror ("fork failed.\n");
		else if (pid == 0)
		{
			//here I will have some scenarios based on the current argument
			// wc < pokemon should keep the result and print it by default, but redirect it in the case of a redirection or a pipe
			// ls | should print by default or redirect in case or redir or pipe
			// ls > pokemon > bakugan > yugioh > scoobydoo should pass to the next one indefinitely, erasing the contents of all but the last arg
			// so read the next three nodes, if there is more nodes after that then redirect to fd[1]
			// after start redirect fd[0] as contents of fd[1]
			close(fd[0]);
			if (matrix->next)
				dup2(fd[1], 1);
			if (!first && exevars->last_output != -1)
				dup2(exevars->last_output, 0);
			close(fd[1]);
			// if (first && !matrix->next)
			// 	exevars->last_output = 0;
			// else if (!first)
			// 	dup2(exevars->last_output, 0);
			// if (matrix->next)
			// 	dup2(fd[1], 1);
			// else
			// 	dup2(1, 1);
			// close (fd[0]);
			execute(matrix->matrix, *envp);
		}
		else
		{
			close (fd[1]);
			exevars->last_output = fd[0];
			close (fd[0]);
			waitpid(pid, &exevars->status, 0);
		}
		it = it->next;
		first = 0;
	}


	// exevars->index == heredoc_n;

	// printf("%s \n", (*envp)->name);

	//
	// while (matrix)
	// {
	// 	if (skip_tokens(&matrix, exevars))
	// 		continue ;
	// 	if (exevars->flag && matrix->operator == '-')
	// 	{
	// 		// heredoc_alone(&matrix, exevars, *envp);
	// 		exevars->index += 2;
	// 		exevars->flag = 0;
	// 		continue ;
	// 	}
		// exe_pipe (matrix, exevars, *envp);
	// 	external_functions(matrix, envp);
	// 	if (matrix)
	// 		matrix = matrix->next;
	// 	exevars->index += 2;
	// 	exevars->flag = 0;
	// }
	// close_all(exevars);
	set_listeners();
}
