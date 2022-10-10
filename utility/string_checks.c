/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:18:22 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/10 02:19:55 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_variable_export(char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 1;
	if (ft_isdigit(*var))
		return (0);
	if (var[0] == '-')
	{
		perror("export : not a valid identifier");
		return (0);
	}
	while (i < len)
	{
		if (!check_variable_char(var[i]))
		{
			perror(var);
			return (0);
		}
		else
			i++;
	}
	return (1);
}

int	check_variable(char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 1;
	if (ft_isdigit(*var))
	{
		return (0);
	}
	while (i < len)
	{
		if (!check_variable_char(var[i]))
			return (0);
		else
			i++;
	}
	return (1);
}

int	check_file(char *arg)
{
	if (access(arg, F_OK) == 0)
		return (0);
	return (-1);
}

int	check_invalid_quote(char *in, int to)
{
	int	i;

	if (to != 0)
		return (0);
	i = to + 1;
	if (!in[i])
		return (1);
	while (in[i])
	{
		if (in[i] == in[to])
		{
			if (i - 1 == to)
				return (i);
			return (0);
		}
		i++;
	}
	return (i);
}
