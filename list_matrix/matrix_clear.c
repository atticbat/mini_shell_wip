/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 02:04:51 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/17 12:38:14 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	matrix_clear(t_matrix **lst, void (*del)(void *))
{
	t_matrix	*buffer;
	int			i;

	buffer = *lst;
	while (buffer != NULL)
	{
		i = 0;
		while (buffer->matrix && buffer->matrix[i] != NULL)
		{
			del(buffer->matrix[i]);
			i++;
		}
		if (buffer->matrix)
			del(buffer->matrix);
		buffer = buffer->next;
		free(*lst);
		*lst = buffer;
	}
	free(*lst);
	lst = NULL;
}
