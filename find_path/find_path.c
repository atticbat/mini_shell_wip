/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:22:39 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/16 01:07:01 by khatlas          ###   ########.fr       */
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

// void	path_arg2(char **paths, t_execute temp, t_general *gen)
// {
// 	int		i;
// 	char	*part_path;
// 	char	*path;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		part_path = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(part_path, temp.arg2[0]);
// 		free (part_path);
// 		if (access(path, F_OK) == 0)
// 		{
// 			gen->cmd_path2 = path;
// 			free_paths(paths);
// 			return ;
// 		}
// 		i++;
// 	}
// }

// void	path_arg1(char **paths, t_execute temp, t_general *gen)
// {
// 	int		i;
// 	char	*part_path;
// 	char	*path;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		part_path = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(part_path, temp.arg1[0]);
// 		free (part_path);
// 		if (access(path, F_OK) == 0)
// 		{
// 			gen->cmd_path1 = path;
// 			if (temp.arg2 == NULL)
// 			{
// 				free_paths(paths);
// 				return ;
// 			}
// 			break ;
// 		}
// 		free (path);
// 		i++;
// 	}
// }

// int	find_path(t_general *gen, t_execute temp)
// {
// 	char	**paths;
// 	int		flag;

// 	flag = 0;
// 	paths = NULL;
// 	gen->cmd_path1 = NULL;
// 	paths = ft_split(gen->path, ':');
// 	path_arg1(paths, temp, gen);
// 	path_arg2(paths, temp, gen);
// 	return (-1);
// }

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
