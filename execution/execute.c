/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:15:13 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/05 17:39:41 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_prep(t_general *gen)
{
	t_execute	exevars;
	t_matrix	*matrix;

	matrix = gen->matrix;
	ft_bzero(&exevars, sizeof(t_execute));
	gen->error_no = exe_cmd (gen->matrix, &exevars, &gen->envp);
	return (gen->error_no);
}
