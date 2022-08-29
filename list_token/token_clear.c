/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 02:04:51 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/29 01:41:03 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_clear(t_token **lst, void (*del)(void *))
{
	t_token	*buffer;

	buffer = *lst;
	while (buffer != NULL)
	{
		if (buffer->content)
			del(buffer->content);
		buffer = buffer->next;
		free(*lst);
		*lst = buffer;
	}
	free(*lst);
	lst = NULL;
}
