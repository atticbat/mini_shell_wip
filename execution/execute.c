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

static void	open_pipes(int pipe_count, int *pipefds)
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
}

int	execute_prep(t_general *gen)
{
	t_execute	exevars;
	t_matrix	*matrix;

	matrix = gen->matrix;
	ft_bzero(&exevars, sizeof(t_execute));
	exevars.pipe_count = count_pipes(gen->matrix);
	exevars.pipefds = malloc (sizeof (int) * (exevars.pipe_count * 2));
	open_pipes(exevars.pipe_count, exevars.pipefds);
	exevars.index = 0;
	exe_cmd (gen->matrix, &exevars, &gen->envp);
	return (0);
}
