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

void	env_clear(t_env **lst, void (*del)(void *))
{
	t_env	*buffer;

	buffer = *lst;
	while (buffer != NULL)
	{
		del(buffer->name);
		del(buffer->content);
		buffer = buffer->next;
		free(*lst);
		*lst = buffer;
	}
	free(*lst);
	lst = NULL;
}
