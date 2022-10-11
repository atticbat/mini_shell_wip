/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:44:17 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/11 18:46:51 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_replace_exe(t_env **envp, char *add, char *name)
{
	t_env	*it;
	size_t	len;

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

int	ft_export_replace_two(t_env **envp, char *add, char *name)
{
	t_env	*it;
	size_t	len;

	if (!envp || !*envp || !(*envp)->next || !add)
		return (-1);
	it = *envp;
	len = ft_strlen(name);
	while (it != NULL)
	{
		if (!ft_strncmp(it->name, name, len) && ft_strlen(it->name) == len)
		{
			free (it->content);
			it->content = ft_strdup(add);
			break ;
		}
		it = it->next;
	}
	return (0);
}
