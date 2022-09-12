/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 01:44:45 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/17 12:38:19 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	matrix_delone(t_matrix *lst, void (*del)(void *))
{
	int	i;

	i = 0;
	while (lst->matrix && lst->matrix[i] != NULL)
	{
		del(lst->matrix[i]);
		i++;
	}
	if (lst->matrix)
		del(lst->matrix);
	free(lst);
}
