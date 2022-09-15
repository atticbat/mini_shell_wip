/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:00:45 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/15 23:15:17 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_pipe_count(int pipe_count, int *pipefds)
{
	int	i;
	
	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			printf("piping fails\n");
			exit (-1);
		}
		i++;
	}
	return i;
}

void	exe_cmd(t_matrix *matrix, int pipe_count, t_env **envp)
{
	int	status;
	int	i;
	int	j;
	int	*pipefds;

	pipefds = malloc (sizeof (int) * (pipe_count * 2));
	i = error_pipe_count(pipe_count, pipefds);
	j = 0;
	if (matrix && matrix->operator == '-')
	{
		exe_heredoc(matrix, pipe_count, pipefds, *envp);
		matrix = matrix->next;
		if (matrix)
			matrix = matrix->next;
	}
	while (matrix)
	{
		if (matrix->operator == '|')
		{
			matrix = matrix->next;
			continue ;
		}
		if (matrix->operator == '>' || matrix->operator == '+' \
		|| matrix->operator == '<' || matrix->operator == '-')
		{
			matrix = matrix->next;
			if (matrix)
				matrix = matrix->next;
			continue ;
		}
		exe_pipe (matrix, pipe_count, pipefds, j, *envp);
		if (cmd_searchlst(matrix->matrix[0]) == EXPORT_CMD)
			ft_export(matrix->matrix, envp);
		else if (cmd_searchlst(matrix->matrix[0]) == UNSET_CMD)
			ft_unset(matrix->matrix, envp);
		else if (cmd_searchlst(matrix->matrix[0]) == CD_CMD)
			ft_cd(matrix->matrix);
		else if (cmd_searchlst(matrix->matrix[0]) == EXIT_CMD)
			exit(0);
		if (matrix)
			matrix = matrix->next;
		j += 2;
	}
	i = 0;
	while (i < pipe_count * 2)
	{
		close (pipefds[i]);
		i++;
	}
	i = 0;
	while (i < pipe_count + 1)
	{
		wait (&status);
		i++;
	}
}
