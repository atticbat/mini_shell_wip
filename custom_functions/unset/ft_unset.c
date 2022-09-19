/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 08:25:31 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/19 10:36:04 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_unset_exe(t_env **envp, char *name)
{
	t_env	*it;
	t_env	*it2;
	size_t	len;

	if (!envp || !*envp || !(*envp)->next || !name)
		return (-1);
	len = ft_strlen(name);
	it = *envp;
	it2 = it->next;
	while (it2->next != NULL)
	{
		if (!ft_strncmp(it2->name, name, len) && ft_strlen(it2->name) == len)
			break ;
		it = it2;
		it2 = it2->next;
	}
	it->next = it2->next;
	free (it2->name);
	free (it2->content);
	return (0);
}

void	ft_unset(t_token *it, t_env **envp)
{
	t_env	*existing;

	if (it->next && it->next->content \
		&& ft_strchr(it->next->content, '\\'))
	{
		printf("unset: not a valid identifier\n");
		return ;
	}
	if (!it || !it->next || !it->next->content)
		return ;
	if (!check_variable_str(it->next->content))
	{
		printf("unset: not a valid identifier\n");
		return ;
	}
	it = it->next;
	existing = find_env(*envp, it->content);
	if (existing)
	{
		if (ft_unset_exe(envp, existing->name))
			return ;
	}
}
