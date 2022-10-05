/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:42:17 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/06 00:42:24 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*construct_line(char *name, char *content, char *end)
{
	char	*final;
	char	*buffer;

	final = NULL;
	buffer = NULL;
	final = ft_strjoin(name, "=");
	buffer = ft_strjoin(final, content);
	free (final);
	final = ft_strjoin(buffer, end);
	free (buffer);
	return (final);
}

char	*generate_env(t_env *envp)
{
	t_env	*it;
	char	*final;
	char	*buffer;

	final = NULL;
	if (!envp || !envp->name || !envp->content)
		exit (-1);
	it = envp;
	final = construct_line(it->name, it->content, "\n");
	it = it->next;
	while (it != NULL)
	{
		if (it->next != NULL)
			buffer = construct_line(it->name, it->content, "\n");
		else
			buffer = construct_line(it->name, it->content, "\0");
		final = ft_strjoinfree(final, buffer);
		it = it->next;
	}
	return (final);
}

void	ft_env(t_env *envp)
{
	char	*final;

	final = generate_env(envp);
	printf("%s\n", final);
	free (final);
}
