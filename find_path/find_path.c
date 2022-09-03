/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:22:39 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/03 18:41:12 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_paths(char **paths)
{
    int i;

    i = 0;
    while (paths[i] != NULL)
    {
        free (paths[i]);
        i++;
    }
    free (paths);
}

int     check_valid_path(t_general *gen, char *content)
{
    char    **paths;
    char    *part_path;
    char    *path;
    int     i;

    if ((!ft_strncmp(content, "unset", 5) && ft_strlen(content) == 5) \
        || (!ft_strncmp(content, "export", 6) && ft_strlen(content) == 6) \
        || (!ft_strncmp(content, "exit", 4) && ft_strlen(content) == 4))
        return (0);
    paths = NULL;
    gen->cmd_path = NULL;
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
            return (0);
        }
        i++;
    }
    free_paths(paths);
    return (-1);
}

int     find_path(t_general *gen, char *content)
{
    char    **paths;
    char    *part_path;
    char    *path;
    int     i;

    paths = NULL;
    gen->cmd_path = NULL;
    paths = ft_split(gen->path, ':');
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, content);
        free (part_path);
        if (access(path, F_OK) == 0)
        {
            gen->cmd_path = path;
            free_paths(paths);
            return (0);
        }
        i++;
    }
    free_paths(paths);
    return (-1);
}