/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:43:40 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/16 01:30:33 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	check_env(char *content)
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
			return ;
		}
		i++;
	}
	free_paths(paths);
}

int	check_valid_path(char *content)
{
	if ((!ft_strncmp(content, "unset", 5) && ft_strlen(content) == 5) \
		|| (!ft_strncmp(content, "export", 6) && ft_strlen(content) == 6) \
		|| (!ft_strncmp(content, "exit", 4) && ft_strlen(content) == 4))
		return (0);
	check_env(content);
	return (-1);
}
