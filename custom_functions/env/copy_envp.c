/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:58:52 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/19 17:18:49 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_eq(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_env_name(char *str)
{
	int		eq;

	if (!str)
		return (NULL);
	eq = find_eq(str);
	if (eq < 0)
		return (NULL);
	return (ft_substr(str, 0, eq));
}

char	*extract_env_content(char *str)
{
	int		eq;

	if (!str)
		return (NULL);
	eq = find_eq(str);
	if (eq < 0)
		return (NULL);
	return (ft_strdup(str + eq + 1));
}

int	copy_envp(char **envp, t_general *gen)
{
	int		index;
	char	*buffer;
	char	*buffer2;

	index = 0;
	buffer = NULL;
	gen->envp = NULL;
	if (!envp || !*envp)
		return (-1);
	while (envp[index] != NULL)
	{
		buffer = extract_env_name(envp[index]);
		buffer2 = extract_env_content(envp[index]);
		if (!buffer || !buffer2)
		{
			gen->error_no = -1;
			return (gen->error_no);
		}
		env_add_back(&gen->envp, env_new(buffer, buffer2, 0));
		index++;
	}
	return (0);
}
