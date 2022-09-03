/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 01:35:05 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/03 19:23:53 by khatlas          ###   ########.fr       */
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

void    ft_echo(t_matrix **it, t_general *gen, int *flag)
{
    if ((*it)->matrix[1] && !ft_strncmp((*it)->matrix[1], "-n", 2) \
        && !parse_nl_flag((*it)->matrix[1]))
    {
        *flag = 1;
        gen->str = ft_echo_exe((*it)->matrix + 2);
    }
    else
        gen->str = ft_echo_exe((*it)->matrix + 1);
}