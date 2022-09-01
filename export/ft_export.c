/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 23:04:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/01 14:07:48 by khatlas          ###   ########.fr       */
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

void    ft_export(t_token *it, t_general *gen)
{
    //need to break this down into individual function
    char    *buffer;
    char    *final;
    t_env   *existing;

    final = NULL;
    it = it->next;
    buffer = it->content;
    if (!buffer || !it->next || !check_variable(buffer))
        return ;
    printf("I get here!\n");
    existing = find_env(gen->envp, buffer);
    it = it->next;
    if (!it->content || it->content[0] != '=')
        return ;
    final = ft_strjoin(buffer, it->content);
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