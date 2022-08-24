/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:43:37 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/24 14:58:04 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset(t_general *gen, t_token **head, char *inpt)
{
    gen->error_no = 0;
    gen->str = NULL;
    token_clear(head, free);
	if (inpt)
		free (inpt);
}

int     check_variable(char *var)
{
    int i = 1;
	int len = 0;

    len = strlen(var);
	if(ft_isdigit(*var) && ft_isalpha(*(var + i)))	// 1 1
	{
		return (0);
    }
    // printf("flag isaplha %d\n", ft_isalpha(*(var + i)));
    while (i < len)
    {
        // printf("valores de str %c\n", (var[i]));
	    if ((*(var + i)) < 48 || ((*(var + i)) >= 58 && (*(var + i)) <= 64) \
        || ((*(var + i)) >= 91 && (*(var + i)) < 95) \
        || ((*(var + i)) > 95 && (*(var + i)) <= 96) \
        || ((*(var + i)) >= 123 && (*(var + i)) <= 127))
        {
            return(0);
        }
        else
            i++;
    }
	return (1);
}
