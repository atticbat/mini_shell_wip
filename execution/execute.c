/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:15:13 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/08 20:58:51 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_prep(t_general *gen)
{
	t_execute	exevars;
	t_matrix	*matrix;

	matrix = gen->matrix;
	ft_bzero(&exevars, sizeof(t_execute));
	exe_cmd (gen->matrix, &exevars, gen);
	remove_files();
	return (gen->error_no);
}
