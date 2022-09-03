/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 01:38:25 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/17 12:38:03 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	matrix_add_back(t_matrix **lst, t_matrix *new)
{
	t_matrix	*buffer;

	if (new == NULL)
		;
	else if (*lst)
	{
		buffer = matrix_last(*(lst));
		buffer->next = new;
	}
	else
		*lst = new;
}
