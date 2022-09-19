/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:36:17 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/17 01:23:20 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_bracketed(char *content, int *i, int start, t_env *envp)
{
	int		index_change;
	char	*buffer;
	char	*final;

	buffer = NULL;
	index_change = 0;
	buffer = ft_substr(content, start + 2, *i - start - 1);
	final = ft_getenv(envp, buffer);
	if (!final)
		final = ft_strdup("");
	else
		final = ft_getenv(envp, buffer);
	index_change = ft_strlen(final) - 1 - (*i - start - 1);
	free (buffer);
	buffer = ft_substr(content, 0, start);
	final = ft_strjoinfree(buffer, final);
	buffer = ft_substr(content, *i + 2, ft_strlen(content + *i + 2));
	final = ft_strjoinfree(final, buffer);
	*i += index_change - 1;
	return (final);
}

char	*extract_regular(char *content, int *i, int start, t_env *envp)
{
	int		index_change;
	char	*buffer;
	char	*final;

	buffer = NULL;
	index_change = 0;
	buffer = ft_substr(content, start + 1, *i - start);
	final = ft_getenv(envp, buffer);
	if (!final)
		final = ft_strdup("");
	else
		final = ft_getenv(envp, buffer);
	index_change = ft_strlen(final) - 1 - (*i - start);
	free (buffer);
	buffer = ft_substr(content, 0, start);
	final = ft_strjoinfree(buffer, final);
	buffer = ft_substr(content, *i + 1, ft_strlen(content + *i + 1));
	final = ft_strjoinfree(final, buffer);
	*i += index_change - 1;
	return (final);
}

char	*extract_q_mark(char *content, int start, int last_return)
{
	char	*buffer;
	char	*final;

	buffer = NULL;
	final = ft_itoa(last_return);
	if (!final)
		final = ft_strdup("0");
	free (buffer);
	buffer = ft_substr(content, 0, start);
	final = ft_strjoinfree(buffer, final);
	buffer = ft_substr(content, start + 2, ft_strlen(content + start + 2));
	final = ft_strjoinfree(final, buffer);
	return (final);
}

char	*expand_dquote(char *content, t_env *envp, int last_return)
{
	int		i;
	char	*buffer;
	char	*final;

	buffer = NULL;
	i = 0;
	final = strdup(content);
	while (final[i] != '\0')
	{
		if (final[i] == '$' && final[i + 1] == '?')
			buffer = extract_q_mark(final, i, last_return);
		else if (final[i] == '$')
			buffer = extract_variable(final, &i, envp);
		if (buffer)
		{
			free (final);
			final = buffer;
			buffer = NULL;
		}
		i++;
	}
	return (final);
}
