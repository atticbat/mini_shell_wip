/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 01:35:05 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/05 13:09:28 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static char *ft_echo_exe(char **it)
{
    char    *buffer;
    char    *final;
    int     i;

    if (!it || !*it)
        return (NULL);
    final = ft_strdup(it[0]);
    i = 1;
    while (it[i] != NULL)
    {
        buffer = ft_strdup(it[i]);
        final = ft_strjoinfree(final, buffer);
        i++;
    }
    return (final);
}

static int  parse_nl_flag(char *content)
{
    int i;

    i = 1;
    if (!content || !*(content + 1))
        return (-1);
    while (content[i] != '\0')
    {
        if (content[i] == ' ' && content[i + 1] == '\0')
            return (0);
        else if (content[i] != 'n')
            return (-1);
        i++;
    }
    return (0);
}

void    ft_echo(t_execute it, t_general *gen, int *flag)
{
    if (it.arg1[1] && !ft_strncmp(it.arg1[1], "-n", 2) \
        && !parse_nl_flag(it.arg1[1]))
    {
        *flag = 1;
        gen->str = ft_echo_exe(it.arg1 + 2);
    }
    else
        gen->str = ft_echo_exe(it.arg1 + 1);
}