/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:18:22 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/19 00:23:13 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			printf("export: '%s': not a valid identifier\n", var);
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
