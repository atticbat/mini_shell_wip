/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:43:37 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/25 15:08:33 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset(t_general *gen, t_token **head, char *inpt)
{
    ft_bzero(gen, sizeof(t_general));
    token_clear(head, free);
	if (inpt)
		free (inpt);
}

int     check_variable(char *var, int len)
{
    int i;
    
    i = 0;
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


// void check_cmd(t_token **head,int flag)
// {
//     flag = 0;
//     // printf("%d cmpr\n", token_searchlst(*head));

//     switch (token_searchlst(*head))
//     {
//         case 1: //echo
//             gen->str = ft_echo(&it);

//         case 2: //cd
//         case 3: //pwd
//         case 4: //export
//         case 5: //unset
//         case 6: //env
//         case 7: //exit
        
//         break;
    
//     default:
//         break;
//     }

//     // return(flag);
// }
