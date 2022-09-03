/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_searchlst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:21:51 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/03 12:30:18 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int  ft_strcmpc(char type, char c)
{
    if(type == c)
        return (1);
    return(0);
}

// int	echo_cases(char *content, int len)
// {
// 	if(!(ft_strncmp((head)->content, "echo",len)))
//     	return (ECHO_CMD);
// 	else if(!(ft_strncmp((head)->content, "echo ",len)))
//     	return (ECHO_CMD);
// 	return (0);
// }

int cmd_searchlst(t_token *head)
{
	int len;

	len = ft_strlen((head->content))+1;
    // Initialize current
	// printf("valor compare : %d \n",!(ft_strncmp((head)->content, "echo",4)));
    // while (head != NULL)
    // {
		//encontramos el tipo y comando
        if (ft_strcmpc((head)->type, 'a'))
		{
			if(!(ft_strncmp((head)->content, "echo",len)))
            	return (ECHO_CMD);
			else if(!(ft_strncmp((head)->content, "cd",len)))
				return (CD_CMD);
			else if(!(ft_strncmp((head)->content, "pwd",len)))
			 	return (PWD_CMD);
			else if(!(ft_strncmp((head)->content, "export",len)))
			 	return (EXPORT_CMD);
			else if(!(ft_strncmp((head)->content, "unset",len)))
			 	return (UNSET_CMD);
			else if(!(ft_strncmp((head)->content, "env",len)))
			 	return (ENV_CMD);
			else if(!(ft_strncmp((head)->content, "exit",len)))
			 	return (EXIT_CMD);
			else
				return(EXTER_CMD);
		}
        // head = head->next;
    // }
    return 0;
}

int cmd_check_contained(t_token *head)
{
	//function just checks if arg contains a function
    if (ft_strcmpc((head)->type, 'a'))
	{
		if(!(ft_strncmp((head)->content, "echo", 4)))
        	return (ECHO_CMD);
		if(!(ft_strncmp((head)->content, "cd", 2)))
			return (CD_CMD);
		if(!(ft_strncmp((head)->content, "pwd", 3)))
			return (PWD_CMD);
		if(!(ft_strncmp((head)->content, "export", 6)))
			return (EXPORT_CMD);
		if(!(ft_strncmp((head)->content, "unset", 5)))
			return (UNSET_CMD);
		if(!(ft_strncmp((head)->content, "env", 3)))
			return (ENV_CMD);
		if(!(ft_strncmp((head)->content, "exit", 4)))
			return (EXIT_CMD);
	}
    return (0);
}