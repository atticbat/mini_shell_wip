/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 23:04:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/18 22:21:46 by aparedes         ###   ########.fr       */
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
	it->next = env_new(extract_env_name(add), extract_env_content(add), 1);
	it = it->next;
	it->next = it2;
	return (0);
}

static void	check_existing(t_env **envp, char *final, t_env *existing)
{
	if (existing)
	{
		if (ft_export_replace_exe(envp, final, existing->name))
			free (final);
	}
	else
	{
		if (ft_export_exe(envp, final))
			free (final);
	}
}
static int	check_equals(char *var)
{
	int		i;
	int		n_eg;
	char	*temp;

	i = 0;
	n_eg = 0;
	temp = var;
	while (i < (int)ft_strlen(temp))
	{
		if (temp[i] == '=')
			n_eg += 1;
		i++;
	}
	if (n_eg > 1)
		return (1);
	return (0);
} 

static char	*get_name(char *it)
{
	int		i;

	i = 0;
	if (!it)
		return (NULL);
	if(check_equals(it))
		return (NULL);
	while (it[i])
	{
		if (it[i + 1] == '=')
			return (ft_substr(it, 0, i));
		i++;
	}
	return (NULL);
}

void	ft_export(t_token *it, t_env **envp)
{
	char	*buffer;
	char	*final;
	t_env	*existing;

	final = NULL;
	it = it->next;
	if(it->next && it->next->content
		&& ft_strchr(it->next->content, '\\'))
	{
		printf("export: not a valid identifier\n");
		return ;
	}
	buffer = get_name(it->content);
	if (!buffer || !check_variable(buffer))
		return ;
	existing = find_env(*envp, buffer);
	free (buffer);
	if (!(it->content) || !ft_strchr(it->content, '='))
		return ;
	final = ft_strdup(it->content);
	check_existing (envp, final, existing);
	free (final);
}
