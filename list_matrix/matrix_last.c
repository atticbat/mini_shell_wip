/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 01:35:04 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/17 12:38:27 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_matrix	*matrix_last(t_matrix *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
