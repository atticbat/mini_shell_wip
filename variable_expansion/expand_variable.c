/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:21:02 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/12 17:02:02 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_variable(t_general *gen)
{
	char	*buffer;
	t_token	*iterator;

	if (!gen->tokens)
		return (-1);
	buffer = NULL;
	iterator = gen->tokens;
	while (iterator != NULL)
	{
		if (iterator->type == '-' && iterator->next)
		{
			iterator = iterator->next;
			if (iterator->type == 's' || iterator->type == 'd')
				buffer = ft_strjoin(">", iterator->content);
			else
				buffer = ft_strjoin("<", iterator->content);
			iterator->type = 'a';
			free (iterator->content);
			iterator->content = buffer;
		}
		if (iterator->type == '$' && !ft_strncmp(iterator->content, "?", 1))
		{
			iterator->type = 'a';
			free (iterator->content);
			iterator->content = ft_itoa(gen->last_return);
		}
		else if (iterator->type == '$')
		{
			iterator->type = 'a';
			buffer = ft_getenv(gen->envp, iterator->content);
			if (!buffer)
				buffer = ft_strdup("");
			free (iterator->content);
			iterator->content = buffer;
		}
		else if (iterator->type == 'd')
		{
			iterator->type = 'a';
			buffer = expand_dquote(iterator->content, gen->envp, gen->last_return);
			free (iterator->content);
			iterator->content = buffer;
		}
		else if (iterator->type == 's')
			iterator->type = 'a';
		iterator = iterator->next;
	}
	return (0);
}
