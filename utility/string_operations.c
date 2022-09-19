/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:49:08 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/31 12:50:38 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg_end(char *in)
{
	int	i;

	i = 0;
	while (in[i] != '\0' && ft_strchr(WHITESPACE, in[i]))
		i++;
	if (i == 0)
		return (0);
	if (in[i] == '\0' || ft_strchr(TOKENS, in[i]))
		return (0);
	return (1);
}

char	*append_space(char *in, char *str, int to)
{
	char	*final;

	final = str;
	if (in[to + 1] != '\0' && check_arg_end(in + (to + 1)))
	{
		final = ft_strjoin(str, " ");
		free (str);
	}
	return (final);
}
