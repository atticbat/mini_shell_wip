/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:05:17 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/27 21:23:11 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *extract_home_path(char cwd[PATH_MAX])
{
    char    *buffer;
    int     i;
    int     j;

    i = 0;
    j = 0;
    buffer = NULL;
    while (cwd[i] != '\0')
    {
        if (cwd[i] == '/')
            j++;
        if (j == 3)
        {
            buffer = ft_substr(cwd, 0, i + 1);
            break ;
        }
        i++;
    }
    return (buffer);
}

static int  cd_no_arg(void)
{
    char    cwd[PATH_MAX];
    char    *buffer;

    getcwd(cwd, PATH_MAX);
    buffer = extract_home_path(cwd);
    if (chdir(buffer) != 0) 
    {
        perror("chdir() failed");
        return (-1);
    }
    if (buffer)
        free (buffer);
    return (0);
}

int ft_cd(t_token *it)
{
    it = it->next;
    if (it == NULL)
    {
        if (!cd_no_arg())
            return (0);
        else
            return (-1);
    }
    else if (it->content[ft_strlen(it->content) - 1] == ' ')
        it->content[ft_strlen(it->content) - 1] = '\0';
    if (it != NULL && chdir(it->content) != 0) 
    {
        perror("chdir() failed");
        return (-1);
    }
    return (0);
}