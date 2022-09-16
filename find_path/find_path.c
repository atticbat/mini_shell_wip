/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:22:39 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/17 00:50:11 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
	{
		free (paths[i]);
		i++;
	}
	free (paths);
}

char	*find_path_str(char *name)
{
	char	**paths_split;
	char	*part_path;
	char	*path;
	int		i;
	char	*genpath;

	genpath = getenv("PATH");
	paths_split = ft_split(genpath, ':');
	i = 0;
	while (paths_split[i])
	{
		part_path = ft_strjoin(paths_split[i], "/");
		path = ft_strjoin(part_path, name);
		free (part_path);
		if (access(path, F_OK) == 0)
		{
			free_paths(paths_split);
			return (path);
		}
		free (path);
		i++;
	}
	if (paths_split)
		free_paths(paths_split);
	return (NULL);
}
