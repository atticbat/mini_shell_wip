/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:49:08 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/11 18:19:23 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_equals(char *var)
{
	int		i;
	int		n_eg;
	char	*temp;

	i = 0;
	n_eg = 0;
	temp = var;
	while (i < (int)ft_strlen(temp))
	{
		if (temp[i] == '=')
			n_eg += 1;
		i++;
	}
	if (n_eg > 1)
		return (1);
	return (0);
}

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

char	*get_name(char *it)
{
	int		i;

	i = 0;
	if (!it)
		return (NULL);
	if (check_equals(it))
		return (ft_strdup(it));
	while (it[i])
	{
		if (it[i + 1] == '=')
			return (ft_substr(it, 0, i + 1));
		i++;
	}
	return (NULL);
}
