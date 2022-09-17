/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:48:08 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/18 00:41:16 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_variable_char(char c)
{
    if (c < '-' || (c > '-' && c < '0') || (c >= ':' && c <= '@') \
		|| (c >= '[' && c < '_') || (c > '_' && c <= '`') \
		|| (c >= '{' && c <= 127))
        return(0);
    return (1);
}

int		check_exception_char(char c)
{
    if (c == '!' || c == '=' || c == '#' || c == '%' || c == '*' || c == '+' \
        || c == '-' || c == '/' || c == '.' || c == ':')
        return(1);
    return (0);
}

int		check_arg_char(char c)
{
    if (c < '!' || c == '\"' || (c >= '&' && c <= '*') || c == ';' \
        || c == '<' || c == '>' || c == '?' || c == '`' || c == '\\' \
        || c == '|' || c >= '~' || c == '$')
        return(0);
    return (1);
}

int		check_variable(char *var)
{
    int i;
    int len;

    len = ft_strlen(var);
    i = 1;
	if (ft_isdigit(*var))
	{
		return (0);
    }
    while (i < len)
    {
	    if (!check_variable_char(var[i]))
            return(0);
        else
            i++;
    }
	return (1);
}

int check_format(t_token *var)
{
	int flag;
	
	flag = 1;
	while (var->next != NULL && var->type == 'a')
	{
		var = var->next;
	}
	if ((var->type) == 'd' || (var->type) == 's' || (var->type) == '>' \
		|| (var->type) == '<' ||(var->type ) == '+' || (var->type ) == '|' \
		|| (var->type ) == '-')
	{
		if(var->next == NULL)
			return (0);
		else
			var = var->next;
	}
	while (var->next != NULL)
	{
		if(var->type == 'a')
			break ;
		else
			var = var->next;
	}
	if ((var->type) == 's' || (var->type) == 'd' || (var->type) == '>' \
		|| (var->type) == '<' ||(var->type ) == '+' || (var->type ) == '|' \
		|| (var->type ) == '-')
		flag = 0;
	if(flag == 0)
		return (0);
	return (1);
}