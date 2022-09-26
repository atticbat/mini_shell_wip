/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:48:47 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/26 21:19:46 by aparedes         ###   ########.fr       */
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

// static int	skip_tokens(t_matrix **matrix, t_execute *exevars)
// {
// 	if ((*matrix)->operator == '|')
// 	{
// 		*matrix = (*matrix)->next;
// 		exevars->flag = 1;
// 		return (1);
// 	}
// 	else if (((*matrix)->operator == '>' || (*matrix)->operator == '+' \
// 		|| (*matrix)->operator == '<' || (*matrix)->operator == '-') \
// 		&& !exevars->flag)
// 	{
// 		*matrix = (*matrix)->next;
// 		if (*matrix)
// 			*matrix = (*matrix)->next;
// 		return (1);
// 	}
// 	return (0);
// }

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
static void	exe_pipe_test(t_matrix *matrix, t_env *envp )
{
	/* empezamos haciendo el conteo de los comandos */
	char	*cmd_path;
	char	**arg;
	int		flag_first = 1;
	int		flag_last = 0;


	arg = matrix->matrix;

	cmd_path = find_path_str(arg[0]);
	printf("\npath %s \n", cmd_path);
	if(!matrix)
		return ;
	if (cmd_searchlst(arg[0]) == EXPORT_CMD && !arg[1])
		export_print_vars(envp);
	
	pid_t	pid;
	int		fd[2];
	int		i;

	if (pipe(fd) = -1)
	{
		perror("Fuck me ");
		return ;
	}
	// check of heredoc command
	while(1)
	{
		pid = fork();
		// child
		if (pid == 0)
		{
			if(flag_first == 1 && flag_last == 1 )
			{
				dup2(fd[1])
			}
			
		}
		if (execv(cmd_path, arg) == -1)
			exit (-1);
			}
	// while (1)
	// {
		
	// }

	

}
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
	// exevars->index == heredoc_n;

	// printf("%s \n", (*envp)->name);
	exe_pipe_test(matrix, *envp);

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
