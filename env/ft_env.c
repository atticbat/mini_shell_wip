/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:42:17 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/26 19:26:16 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_env(char **envp)
{
    char    *final;
    char    *buffer;
    int     i;

    i = 1;
    final = ft_strdup(envp[0]);
    buffer = final;
    final = ft_strjoin(final, "\n");
    free (buffer);
    while (envp[i] != NULL)
    {
        buffer = ft_strdup(envp[i]);
        final = ft_strjoinfree(final, buffer);
        if (envp[i + 1] != NULL)
        {
            buffer = final;
            final = ft_strjoin(final, "\n");
            free (buffer);
        }
        i++;
    }
    return (final);
}