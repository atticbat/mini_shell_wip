/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:48:47 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/16 20:40:39 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_alone(t_matrix *matrix, t_execute *exevars, t_env *envp)
{
	if (matrix && matrix->operator == '-')
	{
		exe_heredoc(matrix, exevars, envp);
		matrix = matrix->next;
		if (matrix)
			matrix = matrix->next;
	}
}

static int	skip_tokens(t_matrix **matrix)
{
	if ((*matrix)->operator == '|')
	{
		*matrix = (*matrix)->next;
		return (1);
	}
	if ((*matrix)->operator == '>' || (*matrix)->operator == '+' \
		|| (*matrix)->operator == '<' || (*matrix)->operator == '-')
	{
		*matrix = (*matrix)->next;
		if (*matrix)
			*matrix = (*matrix)->next;
		return (1);
	}
	return (0);
}

static void	external_functions(t_matrix *matrix, t_env **envp)
{
	if (!matrix)
		;
	else if (cmd_searchlst(matrix->matrix[0]) == EXPORT_CMD)
		ft_export(matrix->matrix, envp);
	else if (cmd_searchlst(matrix->matrix[0]) == UNSET_CMD)
		ft_unset(matrix->matrix, envp);
	else if (cmd_searchlst(matrix->matrix[0]) == CD_CMD)
		ft_cd(matrix->matrix);
}

static void	close_all(t_execute *exevars)
{
	int	i;

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

void	exe_cmd(t_matrix *matrix, t_execute *exevars, t_env **envp)
{
	heredoc_alone(matrix, exevars, *envp);
	while (matrix)
	{
		if (skip_tokens(&matrix))
			continue ;
		exe_pipe (matrix, exevars, *envp);
		external_functions(matrix, envp);
		if (matrix)
			matrix = matrix->next;
		exevars->index += 2;
	}
	close_all(exevars);
}
