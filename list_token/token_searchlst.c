/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_searchlst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:21:51 by aparedes          #+#    #+#             */
/*   Updated: 2022/08/24 23:02:17 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int  ft_strcmpc(char type, char c)
{
    if(type == c)
        return (1);
    return(0);
}

int token_searchlst(t_token *head)
{
    // Initialize current
	// printf("valor compare : %d \n",!(ft_strncmp((head)->content, "echo",4)));
    while (head != NULL)
    {
		//encontramos el tipo y comando
        if (ft_strcmpc((head)->type, 'a'))
		{
			if(!(ft_strncmp((head)->content, "echo",4)))
            	return (1);
			if(!(ft_strncmp((head)->content, "cd",2)))
				return (2);
			if(!(ft_strncmp((head)->content, "pwd",3)))
				return (3);
			if(!(ft_strncmp((head)->content, "export",6)))
				return (4);
			if(!(ft_strncmp((head)->content, "unset",5)))
				return (5);
			if(!(ft_strncmp((head)->content, "env",3)))
				return (6);
			if(!(ft_strncmp((head)->content, "exit",4)))
				return (7);
		}
        head = head->next;
    }
    return 0;
}