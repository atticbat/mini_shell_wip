/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:52:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/09 01:40:44 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token *it)
{
	int	i;

	i = 0;
	while (it && it->type == 'a')
	{
		it = it->next;
		i++;
	}
	return (i);
}

static int	find_echo(t_token *it)
{
	if (it && it->content && !ft_strncmp(it->content, "echo", 4) \
		&& ft_strlen(it->content) == 4)
		return (1);
	return (0);
}

char	**extract_matrix(t_token **it)
{
	char	**matrix_c;
	int		len;
	int		i;
	int		echo_flag;

	len = count_args(*it);
	i = 0;
	echo_flag = find_echo(*it);
	matrix_c = malloc (sizeof(char *) * (len + 1));
	matrix_c[len] = NULL;
	while (*it && (*it)->type == 'a')
	{
		matrix_c[i] = ft_strdup((*it)->content);
		if (!echo_flag && matrix_c[i][ft_strlen(matrix_c[i]) - 1] == ' ')
			matrix_c[i][ft_strlen(matrix_c[i]) - 1] = '\0';
		*it = (*it)->next;
		i++;
	}
	return (matrix_c);
}

char	find_next_operator(t_matrix *matrix, char *search)
{
	t_matrix	*it;

	it = matrix;
	while (it)
	{
		if (ft_strchr(search, it->operator))
			return (it->operator);
		it = it->next;
	}
	return ('N');
}
