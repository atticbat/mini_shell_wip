/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_searchlst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:21:51 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/17 19:22:59 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_strcmpc(char type, char c)
{
	if (type == c)
		return (1);
	return (0);
}

int	cmd_searchlst(char *content)
{
	int	len;

	len = ft_strlen(content) + 1;
	if (!(ft_strncmp(content, "echo", len)))
		return (ECHO_CMD);
	else if (!(ft_strncmp(content, "cd", len)))
		return (CD_CMD);
	else if (!(ft_strncmp(content, "pwd", len)))
		return (PWD_CMD);
	else if (!(ft_strncmp(content, "export", len)))
		return (EXPORT_CMD);
	else if (!(ft_strncmp(content, "unset", len)))
		return (UNSET_CMD);
	else if (!(ft_strncmp(content, "env", len)))
		return (ENV_CMD);
	else if (!(ft_strncmp(content, "exit", len)))
		return (EXIT_CMD);
	return (0);
}

int	cmd_check_contained(t_token *head)
{
	if (ft_strcmpc((head)->type, 'a'))
	{
		if (!(ft_strncmp((head)->content, "echo", 4)))
			return (ECHO_CMD);
		if (!(ft_strncmp((head)->content, "cd", 2)))
			return (CD_CMD);
		if (!(ft_strncmp((head)->content, "pwd", 3)))
			return (PWD_CMD);
		if (!(ft_strncmp((head)->content, "export", 6)))
			return (EXPORT_CMD);
		if (!(ft_strncmp((head)->content, "unset", 5)))
			return (UNSET_CMD);
		if (!(ft_strncmp((head)->content, "env", 3)))
			return (ENV_CMD);
		if (!(ft_strncmp((head)->content, "exit", 4)))
			return (EXIT_CMD);
	}
	return (0);
}
