/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 03:26:32 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/19 03:26:49 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_loop(char *content, int *i, t_env *envp, int start)
{
	int	bracket_flag;

	bracket_flag = 0;
	if (content[*i] == '{')
	{
		bracket_flag = 1;
		*i = *i + 1;
	}
	if (!check_variable_char(content[*i]))
		return (NULL);
	while (content[*i] != '\0')
	{
		if (content[*i + 1] == '}' && bracket_flag)
			return (extract_bracketed(content, i, start, envp));
		if (ft_strchr(WHITESPACE, content[*i + 1]) || content[*i + 1] == '\0' \
			|| check_exception_char(content[*i + 1]) || content[*i + 1] == '$')
			return (extract_regular(content, i, start, envp));
		*i = *i + 1;
	}
	return (NULL);
}

char	*extract_variable(char *content, int *i, t_env *envp)
{
	int		start;

	start = *i;
	*i = *i + 1;
	if (ft_strchr(WHITESPACE, content[*i]))
		return (NULL);
	return (extract_loop(content, i, envp, start));
}
