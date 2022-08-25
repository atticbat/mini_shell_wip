/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_searchlst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:21:51 by aparedes          #+#    #+#             */
/*   Updated: 2022/08/25 12:15:02 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int  ft_strcmpc(char type, char c)
{
    if(type == c)
        return (1);
    return(0);
}

int cmd_searchlst(t_token *head)
{
	int len;

	len = ft_strlen((head->content))+1;
    // Initialize current
	// printf("valor compare : %d \n",!(ft_strncmp((head)->content, "echo",4)));
    while (head != NULL)
    {
		//encontramos el tipo y comando
        if (ft_strcmpc((head)->type, 'a'))
		{
			if(!(ft_strncmp((head)->content, "echo",len)))
            	return (ECHO_CMD);
			if(!(ft_strncmp((head)->content, "cd",len)))
				return (CD_CMD);
			if(!(ft_strncmp((head)->content, "pwd",len)))
				return (PWD_CMD);
			if(!(ft_strncmp((head)->content, "export",len)))
				return (EXPORT_CMD);
			if(!(ft_strncmp((head)->content, "unset",len)))
				return (UNSET_CMD);
			if(!(ft_strncmp((head)->content, "env",len)))
				return (ENV_CMD);
			if(!(ft_strncmp((head)->content, "exit",len)))
				return (EXIT_CMD);
		}
        head = head->next;
    }
    return 0;
}