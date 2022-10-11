/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:14:43 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/11 18:29:18 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exit(t_general *gen)
{
	t_token	*temp;

	temp = gen->tokens;
	while (temp)
	{
		if ((temp->type) == '|')
			return (0);
		temp = temp->next;
	}
	return (-1);
}

int	builtin_executions(t_general *gen)
{
	t_token	*it;

	it = gen->tokens;
	if (it->content && check_exit(gen) == -1)
	{
		if (cmd_searchlst(it->content) == EXPORT_CMD && it->next \
			&& it->next->content)
			ft_export(it, gen);
		else if (cmd_searchlst(it->content) == UNSET_CMD && it->next \
			&& it->next->content)
			ft_unset(it, gen);
		else if (cmd_searchlst(it->content) == CD_CMD)
			gen->error_no = ft_cd(gen);
		else if (cmd_searchlst(it->content) == EXIT_CMD)
		{
			if (it->next && it->next->content \
				&& !check_numeric(it->next->content))
				gen->error_no = INVALID_EXIT_ERR;
			else if (it->next && it->next->content)
				gen->error_no = ft_atoi(it->next->content);
			return (-1);
		}
	}
	return (0);
}
