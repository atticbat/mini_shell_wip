/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 23:04:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/19 21:46:44 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (check_equals(it))
		return (NULL);
	while (it[i])
	{
		if (it[i + 1] == '=')
			return (ft_substr(it, 0, i + 1));
		i++;
	}
	return (NULL);
}

void	ft_export(t_token *it, t_general *gen)
{
	char	*buffer;
	char	*final;
	t_env	*existing;

	final = NULL;
	it = it->next;
	if (it->next && it->next->content \
		&& ft_strchr(it->next->content, '\\'))
	{
		printf("export: not a valid identifier\n");
		gen->error_no = 1;
		return ;
	}
	buffer = get_name(it->content);
	if (!buffer || !check_variable_export(buffer))
	{
		printf("export: not a valid identifier\n");
		gen->error_no = 1;
		return ;
	}
	existing = find_env(gen->envp, buffer);
	free (buffer);
	if (!(it->content) || !ft_strchr(it->content, '='))
		return ;
	final = ft_strdup(it->content);
	check_existing (&gen->envp, final, existing);
	free (final);
}
