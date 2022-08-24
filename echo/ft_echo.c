/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 01:35:05 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/21 03:10:53 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char    *ft_echo(t_token **head)
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