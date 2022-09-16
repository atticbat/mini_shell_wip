/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:50:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/16 20:42:29 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_redirections(t_matrix *matrix, t_execute *exevars, \
	t_env *envp)
{
	if (matrix->next && matrix->next->operator != '-' \
	&& matrix->next->operator != '<')
		if (dup2(exevars->pipefds[exevars->index + 1], 1) == -1)
			printf("redirect stdout didnt work!\n");
	if (exevars->index != 0)
		if (dup2(exevars->pipefds[exevars->index - 2], 0) == -1)
			printf("redirect stdin didnt work!\n");
	if (matrix->next && matrix->next->operator == '-')
		if (matrix->next->next->matrix[0])
			ft_heredoc(matrix->next, envp);
	if (matrix->next && matrix->next->operator == '<')
		redirect_left(matrix);
	redirect_right(matrix->next);
}

void	exe_pipe(t_matrix *matrix, t_execute *exevars, t_env *envp)
{
	pid_t	pid;
	int		i;

	pid = fork ();
	if (pid == 0)
	{
		child_redirections(matrix, exevars, envp);
		i = 0;
		while (i < 2 * exevars->pipe_count)
		{
			close(exevars->pipefds[i]);
			i++;
		}
		execute(matrix->matrix, envp);
	}
}

int	count_pipes(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (matrix != NULL)
	{
		if (ft_strchr(OPERATOR, matrix->operator))
			i++;
		matrix = matrix->next;
	}
	return (i);
}

int	find_pipes(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (matrix)
	{
		if (matrix->operator == '|')
			i++;
		matrix = matrix->next;
	}
	return (i);
}

void	execute(char **arg, t_env *envp)
{
	char	cwd[PATH_MAX];
	char	*buffer;

	buffer = find_path_str(arg[0]);
	if (cmd_searchlst(arg[0]) == ECHO_CMD)
		ft_echo(arg);
	else if (cmd_searchlst(arg[0]) == CD_CMD \
		|| cmd_searchlst(arg[0]) == EXPORT_CMD \
		|| cmd_searchlst(arg[0]) == UNSET_CMD \
		|| cmd_searchlst(arg[0]) == EXIT_CMD)
		;
	else if (cmd_searchlst(arg[0]) == PWD_CMD)
		printf("%s\n", getcwd(cwd, PATH_MAX));
	else if (cmd_searchlst(arg[0]) == ENV_CMD)
		ft_env(envp);
	else if (buffer)
	{
		if (execv(buffer, arg) == -1)
			exit (-1);
	}
	exit (0);
}
