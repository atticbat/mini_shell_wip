/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:43:37 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/26 20:11:29 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset(t_general *gen, t_token **head, char *inpt)
{
    if (gen->str)
        free (gen->str);
    ft_bzero(gen, sizeof(t_general));
    token_clear(head, free);
	if (inpt)
		free (inpt);
    inpt = NULL;
    *head = NULL;
}

int     check_variable_char(char c)
{
    if (c < 48 || (c >= 58 && c <= 64) || (c >= 91 && c < 95) \
        || (c > 95 && c <= 96) || (c >= 123 && c <= 127))
        return(0);
    return (1);
}

int     check_variable(char *var)
{
    int i;
    int len;

    len = ft_strlen(var);
    i = 0;
	if(ft_isdigit(*var) && ft_isalpha(*(var + 1)))	// 1 1
	{
		return (0);
    }
    // printf("flag isaplha %d\n", ft_isalpha(*(var + i)));
    printf("var %d\n",check_variable_char(var[i]));
    while (i < len)
    {
        // printf("valores de str %c\n", (var[i]));
	    if (!check_variable_char(var[i]))
            return(0);
        else
            i++;
    }
	return (1);
}
/* TO handle the error we need to confirm the type when it is a quote going on 
    check also the problem with the quotes.

    NOTE : till now >> doesnt create a file just an error.
            same for >
*/
int check_format(t_token *var)
{
    int flag;

    flag = 1;
    while (var->next != NULL && var->type == 'a')
    {
        var = var->next;
    }
    if (var->type == '&' || (var->type) == 34 || (var->type) == 39
        ||  (var->type) == '>' ||(var->type) == '<' ||(var->type ) == '+'
        || (var->type ) == '|' || (var->type ) == '-')
    {
        flag = 0;
        if(var->next == NULL)
            return (0);
        else
            var = var->next;
    }
    while (var->next != NULL)
    {
        if(var->type == 'a')
            flag = 1;        
        else
            var = var->next;
    }
    if (var->type == '&' || (var->type) == 's' || (var->type) == 'd'
        ||  (var->type) == '>' ||(var->type) == '<' ||(var->type ) == '+'
        || (var->type ) == '|' || (var->type ) == '-')
        flag = 0;
    if(flag == 0)
        return (0);
    return (1);
}
