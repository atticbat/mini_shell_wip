/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:37:39 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/24 23:02:52 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_function(t_token **head, t_general *gen)
{
    // t_token *it;
    char    *buffer;

    buffer = NULL;
    if (!head || !*head)
        return (-1);
    int     flag = 0;
    // (void ) gen;
    printf("token: %d\n",token_searchlst(*head));

    switch (token_searchlst(*head))
    {
        case 1: //echo
        {
            // printf("holaaaaaaaa\n");
            if (!ft_strncmp((*head)->content, "-n", 2) && ft_strlen((*head)->content) == 2)
            {
                flag = 1;
                (*head) = (*head)->next;
                (*head) = (*head)->next;
            }
            gen->str = ft_echo(head);
        }
        // case 2: //cd
        // case 3: //pwd
        // case 4: //export
        // case 5: //unset
        // case 6: //env
        // case 7: //exit
        
        break;
    
    default:
        break;
    }
    // it = *head;
    // //hardcode echo contition for now
    // if (!ft_strncmp(it->content, "echo", 4) && ft_strlen(it->content) == 4)
    // {
    //     it = it->next;
    //     it = it->next;
    //     if (!ft_strncmp(it->content, "-n", 2) && ft_strlen(it->content) == 2)
    //     {
    //         flag = 1;
    //         it = it->next;
    //         it = it->next;
    //     }
    //     gen->str = ft_echo(&it);
    // }
    // //temporary output
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