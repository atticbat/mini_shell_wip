/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:21:02 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/26 00:37:48 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_bracketed(char *content, int *i, int start)
{
	int		index_change;
	char	*buffer;
	char	*final;

	buffer = NULL;
	index_change = 0;
	buffer = ft_substr(content, start + 2, *i - start - 1);
	final = getenv(buffer);
	if (!final)
		final = ft_strdup("");
	else
		final = ft_strdup(getenv(buffer));
	index_change = ft_strlen(final) - 1 - (*i - start - 1);
	free (buffer);
	buffer = ft_substr(content, 0, start);
	final = ft_strjoinfree(buffer, final);
	buffer = ft_substr(content, *i + 2, ft_strlen(content + *i + 2));
	final = ft_strjoinfree(final, buffer);
	*i += index_change - 1;
	return (final);
}

static char	*extract_regular(char *content, int *i, int start)
{
	int		index_change;
	char	*buffer;
	char	*final;

	buffer = NULL;
	index_change = 0;
	buffer = ft_substr(content, start + 1, *i - start);
	final = getenv(buffer);
	if (!final)
		final = ft_strdup("");
	else
		final = ft_strdup(getenv(buffer));
	index_change = ft_strlen(final) - 1 - (*i - start);
	free (buffer);
	buffer = ft_substr(content, 0, start);
	final = ft_strjoinfree(buffer, final);
	buffer = ft_substr(content, *i + 1, ft_strlen(content + *i + 1));
	final = ft_strjoinfree(final, buffer);
	*i += index_change - 1;
	return (final);
}

static char	*extract_variable(char *content, int *i)
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
	//if it is space then that means it's not a variable
	//also include alex's valid variable checker here
	if (ft_strchr(TOKENS, content[*i]) || !check_variable(content + *i, 1))
		return (NULL);
	while (content[*i] != '\0')
	{
		if (content[*i + 1] == '}' && bracket_flag)
			return (extract_bracketed(content, i, start));
		//need alex's checker instead of checking for null & $ sign
		if (ft_strchr(WHITESPACE, content[*i + 1]) || content[*i + 1] == '\0' || content[*i + 1] == '$')
			return (extract_regular(content, i, start));
		*i = *i + 1;
	}
	return (final);
}

static char	*expand_dquote(char *content)
{
	int		i;
	char	*buffer;
	char	*final;

	buffer = NULL;
	i = 0;
	final = strdup(content);
	while (final[i] != '\0')
	{
		if (final[i] == '$')
			buffer = extract_variable(final, &i);
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

int	expand_variable(t_token **head, t_general *gen)
{
	char	*buffer;
	t_token	*iterator;

	if (!head || !*head)
		return (-1);
	buffer = NULL;
	iterator = *head;
	if (!iterator->content)
	{
		gen->error_no = -1;
		return (gen->error_no);	
	}
	while (iterator != NULL)
	{
		if (iterator->type == '$')
		{
			iterator->type = 'a';
			if (getenv(iterator->content))
				buffer = ft_strdup(getenv(iterator->content));
			else
				buffer = ft_strdup("");
			free (iterator->content);
			iterator->content = buffer;
		}
		else if (iterator->type == 'd')
		{
			iterator->type = 'a';
			buffer = expand_dquote(iterator->content);
			free (iterator->content);
			iterator->content = buffer;
		}
		iterator = iterator->next;
	}
	return (0);
}
