/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:15:13 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/12 13:43:10 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cases(t_general *gen)
{
	t_execute	temp;
	t_matrix	*matrix;
	int			n_pipes;

	matrix = gen->matrix;
	ft_bzero(&temp, sizeof(t_execute));
	if (matrix)
	{
		temp.arg1 = matrix->matrix;
		matrix = matrix->next;
		if (matrix)
		{
			temp.operator = matrix->operator;
			matrix = matrix->next;
			if (matrix)
				temp.arg2 = matrix->matrix;
		}
	}
	n_pipes = count_pipes(gen->matrix);
	matrix = gen->matrix;
	exe_cmd (matrix, n_pipes, &gen->envp);
	return (0);
}
