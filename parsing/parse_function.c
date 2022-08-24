/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:37:39 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/21 03:31:40 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_function(t_token **head, t_general *gen)
{
    t_token *it;
    char    *buffer;

    buffer = NULL;
    if (!head || !*head)
        return (-1);
    it = *head;
    //hardcode echo contition for now
    int     flag = 0;
    if (!ft_strncmp(it->content, "echo", 4) && ft_strlen(it->content) == 4)
    {
        it = it->next;
        it = it->next;
        if (!ft_strncmp(it->content, "-n", 2) && ft_strlen(it->content) == 2)
        {
            flag = 1;
            it = it->next;
            it = it->next;
        }
        gen->str = ft_echo(&it);
    }
    //
    //temporary output
    if (gen->str)
    {
        printf("%s", gen->str);
        if (flag)
            printf("%%\n");
        else
            printf("\n");
    }
    //
    return (0);
}