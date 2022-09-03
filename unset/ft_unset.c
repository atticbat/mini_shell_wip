/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 08:25:31 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/03 19:29:23 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_unset_exe(t_env **envp, char *name)
{
    t_env   *it;
    t_env   *it2;
    size_t  len;

    if (!envp || !*envp || !(*envp)->next || !name)
        return (-1);
    len = ft_strlen(name);
    it = *envp;
    it2 = it->next;
    while (it2->next != NULL)
    {
        if (!ft_strncmp(it2->name, name, len) && ft_strlen(it2->name) == len)
            break ;
        it = it2;
        it2 = it2->next;
    }
    it->next = it2->next;
    free (it2->name);
    free (it2->content);
    return (0);
}

void ft_unset(t_matrix **it,t_general *gen)
{
        t_env   *existing;

        if (!(*it) || !(*it)->matrix[1])
        {
            gen->error_no = -1;
            return ;
        }
        existing = find_env(gen->envp, (*it)->matrix[1]);
        if (existing)
        {
            if (ft_unset_exe(&gen->envp, existing->name))
            {
                gen->error_no = -1;
                return ;
            }
        }
}