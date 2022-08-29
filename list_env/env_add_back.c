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

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*buffer;

	if (new == NULL)
		;
	else if (*lst)
	{
		buffer = env_last(*(lst));
		buffer->next = new;
	}
	else
		*lst = new;
}
