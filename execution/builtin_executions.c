/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:14:43 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/18 20:49:42 by khatlas          ###   ########.fr       */
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
	return (1);
}

int	builtin_executions(t_general *gen)
{
	t_token	*it;

	it = gen->tokens;
	if (it->content && check_exit(gen) == 1)
	{
		if (cmd_searchlst(it->content) == EXPORT_CMD && it->next \
			&& it->next->content)
			ft_export(it, &gen->envp);
		else if (cmd_searchlst(it->content) == UNSET_CMD && it->next \
			&& it->next->content)
			ft_unset(it, &gen->envp);
		else if (cmd_searchlst(it->content) == CD_CMD)
			ft_cd(it);
		else if (cmd_searchlst(it->content) == EXIT_CMD)
		{
			printf("exit\n");
			return (-1);
		}
	}
	return (0);
}
