/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 01:35:05 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/17 17:49:00 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_echo_exe(char **it)
{
	char	*buffer;
	char	*final;
	int		i;

	if (!it || !*it)
		return (NULL);
	final = ft_strdup(it[0]);
	i = 1;
	while (it[i] != NULL)
	{
		buffer = ft_strdup(it[i]);
		final = ft_strjoinfree(final, buffer);
		i++;
	}
	return (final);
}

static int	parse_nl_flag(char *content)
{
	int	i;

	i = 1;
	if (!content || !*(content + 1))
		return (-1);
	while (content[i] != '\0')
	{
		if (content[i] == ' ' && content[i + 1] == '\0')
			return (0);
		else if (content[i] != 'n')
			return (-1);
		i++;
	}
	return (0);
}

static int	count_nl_flags(char **it)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (it[i])
	{
		if (!parse_nl_flag(it[i]))
			count++;
		i++;
	}
	return (count);
}

void	ft_echo(char **it)
{
	char	*str;
	int		flag;

	str = NULL;
	flag = 0;
	if (it[1] && !ft_strncmp(it[1], "-n", 2) \
		&& !parse_nl_flag(it[1]))
	{
		flag = 1;
		str = ft_echo_exe(it + count_nl_flags(it) + 1);
	}
	else
		str = ft_echo_exe(it + 1);
	if (!str)
		return ;
	if (flag)
		printf("%s", str);
	else
		printf("%s\n", str);
	free (str);
}
