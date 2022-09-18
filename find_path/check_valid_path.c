/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:43:40 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/18 03:46:49 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env(char *content)
{
	int		i;
	char	*part_path;
	char	*path;
	char	**paths;

	paths = NULL;
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, content);
		free (part_path);
		if (access(path, F_OK) == 0)
		{
			free (path);
			free_paths(paths);
			return (0);
		}
		i++;
	}
	free_paths(paths);
	return (-1);
}

// int	check_valid_path(char *content)
// {
// 	if ((!ft_strncmp(content, "unset", 5) && ft_strlen(content) == 5) \
// 		|| (!ft_strncmp(content, "export", 6) && ft_strlen(content) == 6) \
// 		|| (!ft_strncmp(content, "exit", 4) && ft_strlen(content) == 4))
// 		return (0);
// 	if (!check_env(content))
// 		r
// 	return (-1);
// }
