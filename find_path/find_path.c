/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:22:39 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/01 17:05:36 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    find_path(t_general *gen, t_token *lst)
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
            return ;
        }
        i++;
    }
}