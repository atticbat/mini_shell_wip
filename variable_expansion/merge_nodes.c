/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:21:59 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/09 22:55:38 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	combine(t_token *it)
{
	char	*buffer;
	t_token	*temp;

	buffer = NULL;
	buffer = ft_strjoin(it->content, it->next->content);
	if (buffer[ft_strlen(buffer) - 1] == ' ')
		buffer[ft_strlen(buffer) - 1] = '\0';
	if (cmd_searchlst(buffer) || !check_env(buffer))
	{
		temp = it->next->next;
		token_delone(it->next, free);
		free(it->content);
		it->content = ft_strdup(buffer);
		it->next = temp;
		if (it->next && it->next->content && it->next->content[0] == ' ' \
			&& ft_strlen(it->next->content) == 1)
		{
			temp = it->next->next;
			token_delone(it->next, free);
			it->next = temp;
		}
	}
	free (buffer);
}

void	merge_nodes(t_general *gen)
{
	t_token	*it;
	int		flag;

	flag = 1;
	it = gen->tokens;
	while (it)
	{
		if (it->content && it->content[ft_strlen(it->content) - 1] != ' ' \
			&& it->next && it->next->content && flag == 1)
		{
			combine(it);
			flag = 0;
		}
		else if (ft_strchr(OPERATOR, it->type))
			flag = 1;
		it = it->next;
	}
}
