/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:21:02 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/11 18:36:00 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_bracketed(char *content, int *i, int start, t_env *envp)
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

static char	*extract_regular(char *content, int *i, int start, t_env *envp)
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

static char	*extract_variable(char *content, int *i, t_env *envp)
{
	int		bracket_flag;
	char	*final;
	int		start;

	start = *i;
	*i = *i + 1;
	bracket_flag = 0;
	final = NULL;
	if (ft_strchr(WHITESPACE, content[*i]))
		return (NULL);
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
			|| content[*i + 1] == '$')
			return (extract_regular(content, i, start, envp));
		*i = *i + 1;
	}
	return (final);
}

static char	*extract_q_mark(char *content, int start, int last_return)
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

static char	*expand_dquote(char *content, t_env *envp, int last_return)
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

int	expand_variable(t_general *gen)
{
	char	*buffer;
	t_token	*iterator;

	if (!gen->tokens)
		return (-1);
	buffer = NULL;
	iterator = gen->tokens;
	while (iterator != NULL)
	{
		if (iterator->type == '$' && !ft_strncmp(iterator->content, "?", 1))
		{
			iterator->type = 'a';
			free (iterator->content);
			iterator->content = ft_itoa(gen->last_return);
		}
		else if (iterator->type == '$')
		{
			iterator->type = 'a';
			buffer = ft_getenv(gen->envp, iterator->content);
			if (!buffer)
				buffer = ft_strdup("");
			free (iterator->content);
			iterator->content = buffer;
		}
		else if (iterator->type == 'd')
		{
			iterator->type = 'a';
			buffer = expand_dquote(iterator->content, gen->envp, gen->last_return);
			free (iterator->content);
			iterator->content = buffer;
		}
		iterator = iterator->next;
	}
	return (0);
}
