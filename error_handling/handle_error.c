/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:26:08 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/06 19:47:08 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(int error, t_general *gen)
{
	if (error == 1)
	{
		write (2, "you typed exit xddd lmao\n", 25); //temp
		free_all(gen);
		exit (0);
	}
	else if (error)
	{
		write (2, "regular error xdd haha\n", 23); //temp
		reset(gen);
	}
	else
		return (0);
	return (-1);
}