/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:15:13 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/10 04:11:08 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_prep(t_general *gen)
{
	t_execute	exevars;
	t_matrix	*matrix;

	matrix = gen->matrix;
	ft_bzero(&exevars, sizeof(t_execute));
	exevars.pipe_count = find_pipes(gen->matrix);
	exevars.current_pipe = exevars.pipe_count;
	exevars.pids = malloc (sizeof (int) * (exevars.pipe_count + 1));
	exe_cmd (gen->matrix, &exevars, gen);
	remove_files();
	free (exevars.pids);
	return (gen->error_no);
}
