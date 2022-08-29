/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:42:22 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/29 06:32:29 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	count_envp(char **envp)
// {
// 	int		count;

// 	count = 0;
// 	while (envp[count] != NULL)
// 		count++;
// 	return (count);
// }

// char	**copy_envp(char **envp)
// {
// 	char	**final;
// 	int		index;

// 	index = 0;
// 	if (!envp || !*envp)
// 		return (NULL);
// 	final = (char **) malloc (sizeof (char *) * (count_envp(envp) + 1));
// 	while (envp[index] != NULL)
// 	{
// 		final[index] = ft_strdup(envp[index]);
// 		index++;
// 	}
// 	final[index] = NULL;
// 	return (final);
// }

static int	find_eq(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
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
		// printf("buffer1: %s, buffer2: %s\n", buffer, buffer2);
		if (!buffer || !buffer2)
		{
			gen->error_no = -1;
			return (gen->error_no);
		}
		env_add_back(&gen->envp, env_new(buffer, buffer2));
		index++;
	}
	return (0);
}