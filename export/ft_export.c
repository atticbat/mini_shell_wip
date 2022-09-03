/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 23:04:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/03 19:27:13 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_export_replace_exe(t_env **envp, char *add, char *name)
{
    t_env   *it;
    size_t  len;

    if (!envp || !*envp || !(*envp)->next || !add)
        return (-1);
    it = *envp;
    len = ft_strlen(name);
    while (it != NULL)
    {
        if (!ft_strncmp(it->name, name, len) && ft_strlen(it->name) == len)
        {
            free (it->content);
            it->content = extract_env_content(add);
            break ;
        }
        it = it->next;
    }
    return (0);
}

static int  ft_export_exe(t_env **envp, char *add)
{
    t_env   *it;
    t_env   *it2;

    if (!envp || !*envp || !(*envp)->next || !add)
        return (-1);
    it = *envp;
    it2 = it->next;
    while (it2->next != NULL)
    {
        it = it2;
        it2 = it2->next;
    }
    it->next = env_new(extract_env_name(add), extract_env_content(add));
    it = it->next;
    it->next = it2;
    return (0);
}

void    ft_export(t_matrix **it, t_general *gen)
{
    char    *buffer;
    char    *final;
    t_env   *existing;

    final = NULL;
    buffer = (*it)->matrix[1];
    // printf("matrix[0]: %s, matrix[1]: %s\n", (*it)->matrix[0], (*it)->matrix[0]);
    if (!buffer || !check_variable(buffer))
        return ;
    existing = find_env(gen->envp, buffer);
    if (!(*it)->matrix[2] || (*it)->matrix[2][0] != '=')
        return ;
    final = ft_strjoin(buffer, (*it)->matrix[2]);
    if (existing)
    {
        if (ft_export_replace_exe(&gen->envp, final, existing->name))
        {
            free (final);
            gen->error_no = -1;
            return ;
        }
    }
    else
    {
        if (ft_export_exe(&gen->envp, final))
        {
            free (final);
            gen->error_no = -1;
            return ;
        }
    }
    free (final);
}