/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 23:04:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/26 23:36:05 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **ft_export(char **envp, char *add)
{
    char    **new_envp;
    int     i;

    i = 0;
    if (!add)
        return (NULL);
    new_envp = (char **) malloc (sizeof (char *) * (count_envp(envp) + 2));
    while (envp[i] != NULL)
    {
        new_envp[i] = envp[i];
        i++;
    }
    new_envp[i] = ft_strdup(add);
    new_envp[i + 1] = NULL;
    free (envp);
    return (new_envp);
}