/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:00:45 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/16 01:03:17 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	exe_cmd(t_matrix *matrix, t_execute *exevars, t_env **envp)
{
	int	i;

	if (matrix && matrix->operator == '-')
	{
		exe_heredoc(matrix, exevars, *envp);
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
		exe_pipe (matrix, exevars, *envp);
		if (cmd_searchlst(matrix->matrix[0]) == EXPORT_CMD)
			ft_export(matrix->matrix, envp);
		else if (cmd_searchlst(matrix->matrix[0]) == UNSET_CMD)
			ft_unset(matrix->matrix, envp);
		else if (cmd_searchlst(matrix->matrix[0]) == CD_CMD)
			ft_cd(matrix->matrix);
		if (matrix)
			matrix = matrix->next;
		exevars->index += 2;
	}
	i = 0;
	while (i < exevars->pipe_count * 2)
	{
		close (exevars->pipefds[i]);
		i++;
	}
	i = 0;
	while (i < exevars->pipe_count + 1)
	{
		wait (&(exevars->status));
		i++;
	}
}
