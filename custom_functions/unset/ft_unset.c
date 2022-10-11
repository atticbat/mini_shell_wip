/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 08:25:31 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/11 18:24:17 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_unset_exe(t_env **envp, char *name)
{
	t_env	*it;
	t_env	*it2;
	size_t	len;

	if (!envp || !*envp || !(*envp)->next || !name)
		return (1);
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

static int	check_error(t_token *it, t_general *gen)
{
	if (!it || !it->next || !it->next->content)
		return (1);
	if (it->next && it->next->content \
		&& ft_strchr(it->next->content, '\\'))
	{
		perror("unset: not a valid identifier\n");
		gen->error_no = 1;
		return (1);
	}
	if (check_variable_str(it->next->content))
	{
		perror("unset: not a valid identifier\n");
		gen->error_no = 1;
		return (1);
	}
	return (0);
}

void	ft_unset(t_token *it, t_general *gen)
{
	t_env	*existing;

	if (check_error(it, gen))
		return ;
	it = it->next;
	if (it && it->content && it->content[ft_strlen(it->content) - 1] == ' ')
		it->content[ft_strlen(it->content) - 1] = '\0';
	existing = find_env(gen->envp, it->content);
	if (existing)
	{
		if (!ft_strncmp(existing->name, "PATH", 4) && \
			ft_strlen(existing->name) == 4)
		{
			free (existing->content);
			existing->content = ft_strdup("");
		}
		else if (ft_unset_exe(&gen->envp, existing->name))
			return ;
	}
}
