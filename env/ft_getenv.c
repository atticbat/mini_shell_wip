/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:34:58 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/26 20:02:21 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  len_to_chr(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

char    *ft_getenv(char **envp, char *search)
{
    int     i;
    char    *buffer;
    int     len;

    i = 0;
    len = ft_strlen(search);
    buffer = NULL;
    while (envp[i] != NULL)
    {
        if (!ft_strncmp(envp[i], search, len) && len_to_chr(envp[i], '=') == len)
        {
            buffer = ft_strchr(envp[i], '=');
            if (!buffer)
                return (NULL);
            return (ft_strdup(buffer + 1));
        }
        i++;
    }
    return (NULL);
}