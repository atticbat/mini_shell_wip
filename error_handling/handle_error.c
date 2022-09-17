/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:26:08 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/17 18:48:24 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(int error, t_general *gen)
{
	if (error == 1)
	{
		write (2, "minishell $ exit\n", 17);
		free_all(gen);
		erase_temp();
	}
	else if (error == 2)
	{
		write (2, "command not found\n", 18);
		reset(gen);
	}
	else if (error)
	{
		write (2, "regular error xdd haha\n", 23);
		reset(gen);
	}
	else
		return (0);
	return (-1);
}

int	error_extract_var(t_general *gen)
{
	if (ft_strchr(TOKENS, gen->in[gen->to]))
	{
		gen->error_no = -1;
		return (gen->error_no);
	}
	else
		gen->error_no = 0;
	return (gen->error_no);
}
