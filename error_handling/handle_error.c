/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:26:08 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/11 18:00:56 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_bank(int error)
{
	if (error == PERMISSION_ERR)
		write (2, "Permission denied\n", 18);
	else if (error == FAILFORK_ERR)
		write (2, "Fork failure\n", 13);
	else if (error == MALLOC_ERR)
		write (2, "Insufficient memory\n", 20);
	else if (error == SYNTAX_ERR)
		write (2, "Syntax error, unexpected token\n", 31);
	else if (error == INVALID_EXIT_ERR)
		write(2, "exit: numeric argument required\n", 32);
	else if (error == -1)
		write (2, "exit\n", 5);
}

int	handle_error(int error, t_general *gen)
{
	(void) gen;
	error_bank(error);
	if (error)
		return (-1);
	else
		return (0);
}

int	error_extract_var(t_general *gen)
{
	if (ft_strchr(TOKENS, gen->in[gen->to]))
	{
		gen->error_no = 1;
		return (gen->error_no);
	}
	else
		gen->error_no = 0;
	return (gen->error_no);
}
