/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:22:39 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/02 22:00:49 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    find_path(t_general *gen, t_token *lst)
{
    char    **paths;
    char    *part_path;
    char    *path;
    int     i;

    paths = NULL;
    gen->cmd_path = NULL;
    //leak
    paths = ft_split(gen->path, ':');
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, lst->content);
        free (part_path);
        if (access(path, F_OK) == 0)
        {
            gen->cmd_path = path;
            return (0);
        }
        i++;
    }
    return (-1);
}