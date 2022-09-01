/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:01:16 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/01 15:09:28 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    env_find(t_general *gen, char *search)
{
    t_env   *it;
    size_t  len;

    it = gen->envp;
    len = ft_strlen(search);
    while (it != NULL)
    {
        if (!ft_strncmp(search, it->name, len))
        {
            gen->path = ft_strdup(it->content);
            return ;
        }
        it = it->next;
    }
}