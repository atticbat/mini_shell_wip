/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 00:18:22 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/19 17:16:28 by aparedes         ###   ########.fr       */
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

int	check_file(char *arg)
{
	if (access(arg, F_OK) == 0)
		return (0);
	return (-1);
}
