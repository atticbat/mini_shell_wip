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

void	env_delone(t_env *lst, void (*del)(void *))
{
	del(lst->name);
	del(lst->content);
	free(lst);
}
