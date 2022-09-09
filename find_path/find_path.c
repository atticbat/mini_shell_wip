/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:22:39 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/08 15:00:12 by khatlas          ###   ########.fr       */
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
    gen->cmd_path1 = NULL;
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

int     find_path(t_general *gen, t_execute temp)
{
    char    **paths;
    char    *part_path;
    char    *path;
    int     i;
    int     flag;

    flag = 0;
    paths = NULL;
    gen->cmd_path1 = NULL;
    gen->cmd_path2 = NULL;

    paths = ft_split(gen->path, ':');
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, temp.arg1[0]);
        free (part_path);
        if (access(path, F_OK) == 0)
        {
            gen->cmd_path1 = path;
            if (temp.arg2 == NULL)
            {           
                free_paths(paths);
                return(0);
            }
            break;
        }
        free (path);
        i++;
    }
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, temp.arg2[0]);
        free (part_path);
        if (access(path, F_OK) == 0)
        {
            gen->cmd_path2 = path;
            free_paths(paths);
            return (0);
        }
        i++;
    }
    return (-1);
}

char    *find_path_str(char *name)
{
    char    **paths_split;
    char    *part_path;
    char    *path;
    int     i;
    char    genpath[] = "/Users/khatlas/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/khatlas/.brew/bin";

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