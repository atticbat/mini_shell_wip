/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:43:40 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/19 20:44:40 by khatlas          ###   ########.fr       */
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
		free (path);
		i++;
	}
	free_paths(paths);
	return (-1);
}
