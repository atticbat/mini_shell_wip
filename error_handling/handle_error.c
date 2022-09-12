/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:26:08 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/12 13:40:33 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(int error, t_general *gen)
{
	if (error == 1)
	{
		write (2, "you pressed ctrl d xddd lmao\n", 29);
		free_all(gen);
		erase_temp();
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
