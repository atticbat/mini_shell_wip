/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 01:35:05 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/01 14:18:01 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static char *ft_echo_exe(t_token **head)
{
    t_token *iterator;
    char    *buffer;
    char    *final;

    if (!head || !*head)
        return (NULL);
    iterator = *head;
    final = ft_strdup(iterator->content);
    iterator = iterator->next;
    while (iterator != NULL)
    {
        //to do: space type for indicating whether there was a space
        if (iterator->type == 'a')
        {
            buffer = ft_strdup(iterator->content);
            final = ft_strjoinfree(final, buffer);
        }
        else
            break ;
        iterator = iterator->next;
    }
    //will return a complete string that will either be piped into the next bit of code or printed
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

void    ft_echo(t_token *it, t_general *gen, int *flag)
{
    it = it->next;
    if (!ft_strncmp(it->content, "-n", 2) && !parse_nl_flag(it->content))
    {
        *flag = 1;
        it = it->next;
    }
    gen->str = ft_echo_exe(&it);
}