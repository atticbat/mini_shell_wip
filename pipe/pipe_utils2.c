/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:48:47 by aparedes          #+#    #+#             */
/*   Updated: 2022/10/02 16:56:09 by khatlas          ###   ########.fr       */
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
		exevars->last_op = (*matrix)->operator;
		return (1);
	}
	else if ((*matrix)->operator == '>' || (*matrix)->operator == '+' \
		|| (*matrix)->operator == '<' || (*matrix)->operator == '-')
	{
		*matrix = (*matrix)->next;
		if (*matrix)
			*matrix = (*matrix)->next;
		exevars->last_op = (*matrix)->operator;
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
		if (count_operators(*it, OPERATOR))
			dup2(exevars->pipeA[WRITE_END], WRITE_END);
		if (exevars->last_op == '>')
		{
			int	fd;

			fd = open ((*it)->matrix[0], O_TRUNC | O_CREAT | O_WRONLY, 0777);
			dup2(fd, WRITE_END);
			close (fd);
		}
		execute((*it)->matrix, envp);
	}
	else
	{
		close(exevars->pipeA[WRITE_END]);
		dup2(exevars->pipeA[READ_END], READ_END);
		wait(&status);
	}
}

int	exe_cmd(t_matrix *matrix, t_execute *exevars, t_env **envp)
{
	t_matrix	*it;
	int	heredoc_n;
	int	ret_value;

	ret_value = 0;
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

	//redirection file creation
	// it = matrix;
	// char	*buffer;
	// buffer = NULL;
	// while (it)
	// {
	// 	if (skip_tokens(&it, exevars))
	// 		continue ;
	// 	//store last argument for the case of '<'
	// 	if (it->operator == 'F' || it->operator == 'N')
	// 		buffer = it->matrix[0];
	// 	if (it->operator == '>' && it->next)
	// 	{
	// 		it = it->next;
	// 		//create a new file with name of following matrix[0]
	// 		int	fd;

	// 		fd = open (it->matrix[0],  O_WRONLY | O_TRUNC | O_CREAT, 0777);
	// 		close (fd);
	// 	}
	// 	else if (it->operator == '<')
	// 	{
	// 		int	fd;

	// 		fd = open (buffer, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	// 		close (fd);
	// 	}
	// 	else if (it->operator == '+' && it->next)
	// 	{
	// 		it = it->next;
	// 		int	fd;

	// 		fd = open (it->matrix[0], O_WRONLY | O_CREAT, 0777);
	// 		close (fd);		
	// 	}
	// 	else if ((it->operator == '>' || it->operator == '+') && (!it->next || !it->next->matrix))
	// 		perror("Invalid redirection\n");
	// 	it = it->next;
	// }
	//redirection file creation

	//now for executions
	//if there is a redirection or a heredoc then I will set the stdout and stdin respectively as the name of the file, which should be created already

	//so, back to my original idea
	//but this time, using two pipes simultaneously
	
	it = matrix;
	{
		pid_t	pid;

		pid = fork();
		if (pid == -1)
			perror ("Fork failed\n");
		else if (pid == 0)
		{
			while (it)
			{
				if (skip_tokens(&it, exevars))
					continue ;
				execute_children(&it, exevars, *envp);
				exevars->last_arg = it->matrix[0];
				it = it->next;
			}
			exit(0);
		}
		else
			waitpid(pid, &ret_value, exevars->status);
	}
	set_listeners();
	return (ret_value);
}
