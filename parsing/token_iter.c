/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_iter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:23:16 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/16 15:09:51 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	token_iter(t_token *lst, void (*f)(void *))
{
	t_token	*buffer;

	buffer = lst;
	if (lst != NULL)
	{
		while (lst != NULL)
		{
			buffer = buffer->next;
			f(lst->content);
			lst = buffer;
		}
	}
}
