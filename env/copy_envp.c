/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:42:22 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/26 19:02:02 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_envp(char **envp)
{
	int		count;

	count = 0;
	while (envp[count] != NULL)
		count++;
	return (count);
}

char	**copy_envp(char **envp)
{
	char	**final;
	int		index;

	index = 0;
	if (!envp || !*envp)
		return (NULL);
	final = (char **) malloc (sizeof (char *) * (count_envp(envp) + 1));
	while (envp[index] != NULL)
	{
		final[index] = ft_strdup(envp[index]);
		index++;
	}
	final[index] = NULL;
	return (final);
}