/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 23:04:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/29 06:24:08 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_export(t_env **envp, char *add)
{
    t_env   *it;
    t_env   *it2;

    if (!envp || !*envp || !(*envp)->next || !add)
        return (-1);
    it = *envp;
    it2 = it->next;
    while (it2->next != NULL)
    {
        it = it2;
        it2 = it2->next;
    }
    it->next = env_new(extract_env_name(add), extract_env_content(add));
    it = it->next;
    it->next = it2;
    return (0);
}