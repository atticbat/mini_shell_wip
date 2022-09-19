/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:18:57 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/16 17:44:52 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset(t_general *gen)
{
	gen->last_return = gen->error_no;
	gen->error_no = 0;
	gen->to = 0;
	gen->from = 0;
	gen->flag = 0;
	if (gen->tokens)
		token_clear(&gen->tokens, free);
	if (gen->matrix)
		matrix_clear(&gen->matrix, free);
	gen->tokens = NULL;
	gen->matrix = NULL;
}

void	free_all(t_general *gen)
{
	reset(gen);
	env_clear(&gen->envp, free);
}

void	erase_temp(void)
{
	char	**matrix;
	int		tempfile;

	matrix = malloc (sizeof (char *) * 3);
	matrix[0] = ft_strdup("rm -f");
	matrix[1] = ft_strdup(PATH_FILE_1);
	matrix[2] = NULL;
	tempfile = open (PATH_FILE_1, O_CREAT, 0777);
	close (tempfile);
	execv("/bin/rm", matrix);
}
