/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 23:04:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/15 15:06:36 by aparedes         ###   ########.fr       */
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

static int	ft_export_exe(t_env **envp, char *add)
{
	t_env	*it;
	t_env	*it2;

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

static void	check_existing(t_env **envp, char *final, t_env *existing)
{
	if (existing)
	{
		if (ft_export_replace_exe(envp, final, existing->name))
		{
			free (final);
			exit (-1);
		}
	}
	else
	{
		if (ft_export_exe(envp, final))
		{
			free (final);
			exit (-1);
		}
	}
}

void	ft_export(char **it, t_env **envp)
{
	char	*buffer;
	char	*final;
	t_env	*existing;

	final = NULL;
	buffer = it[1];
	if (!buffer || !check_variable(buffer))
		exit (-1);
	existing = find_env(*envp, buffer);
	if (!(it[2]) || it[2][0] != '=')
		exit (-1);
	final = ft_strjoin(buffer, it[2]);
	check_existing (envp, final, existing);
	free (final);
}
