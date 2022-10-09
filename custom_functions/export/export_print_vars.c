/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 20:56:51 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/09 06:24:47 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*construct_line(char *name, char *content, char *end)
{
	char	*final;
	char	*buffer;

	final = NULL;
	buffer = NULL;
	buffer = ft_strjoin("declare -x ", name);
	if (content)
	{
		final = ft_strjoin(buffer, "=\"");
		buffer = ft_strjoin(final, content);
		free (final);
		final = ft_strjoin(buffer, end);
	}
	else
		return (buffer);
	free (buffer);
	return (final);
}

static void	sort_strings(char **strings, int count)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strncmp(strings[i], strings[j], ft_strlen(strings[i])) > 0)
			{
				buffer = strings[i];
				strings[i] = strings[j];
				strings[j] = buffer;
			}
			j++;
		}
	i++;
	}
}

static void	print_strings(t_env *it, int i, char **final)
{
	int	j;

	while (it != NULL && it->user_set)
	{
		final[i] = construct_line(it->name, it->content, "\"\n");
		i++;
		it = it->next;
	}
	j = 0;
	while (j < i)
	{
		printf("%s", final[j]);
		free (final[j]);
		j++;
	}
	free (final);
}

static void	fill_strings(t_env **it, int *i, int *flag, char **final)
{
	t_env	*buffer;

	buffer = NULL;
	while (*it != NULL)
	{
		if ((*it)->user_set == 1)
		{
			buffer = env_last(*it);
			final[*i] = construct_line(buffer->name, buffer->content, "\"\n");
			*flag = 1;
			(*i)++;
			break ;
		}
		final[*i] = construct_line((*it)->name, (*it)->content, "\"\n");
		*it = (*it)->next;
		(*i)++;
	}
}

void	export_print_vars(t_env *envp)
{
	t_env	*it;
	int		i;
	int		flag;
	char	**final;

	final = NULL;
	if (!envp || !envp->name || !envp->content)
		exit (127);
	final = malloc (sizeof (char *) * (env_size(envp)));
	it = envp;
	it = it->next;
	i = 0;
	flag = 0;
	fill_strings(&it, &i, &flag, final);
	sort_strings(final, i - flag);
	print_strings(it, i, final);
}
