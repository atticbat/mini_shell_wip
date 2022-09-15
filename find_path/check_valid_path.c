/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:43:40 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/15 16:00:25 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	check_check(t_general *gen, char *content)
{
	int		i;
	char	*part_path;
	char	*path;
	char	**paths;

	paths = NULL;
	paths = ft_split(gen->path, ':');
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
			return ;
		}
		i++;
	}
	free_paths(paths);
}
	// char	**paths;
	// char	*part_path;
	// char	*path;
	// int		i;
	// i = 0;
	// 	paths = NULL;
	// paths = ft_split(gen->path, ':');

int	check_valid_path(t_general *gen, char *content)
{
	if ((!ft_strncmp(content, "unset", 5) && ft_strlen(content) == 5) \
		|| (!ft_strncmp(content, "export", 6) && ft_strlen(content) == 6) \
		|| (!ft_strncmp(content, "exit", 4) && ft_strlen(content) == 4))
		return (0);
	check_check(gen, content);
	return (-1);
}
	// while (paths[i])
	// {
	// 	part_path = ft_strjoin(paths[i], "/");
	// 	path = ft_strjoin(part_path, content);
	// 	free (part_path);
	// 	if (access(path, F_OK) == 0)
	// 	{
	// 		free (path);
	// 		free_paths(paths);
	// 		return (0);
	// 	}
	// 	i++;
	// }
	// free_paths(paths);
