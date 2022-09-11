/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:21:02 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/11 18:41:02 by aparedes         ###   ########.fr       */
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
		iterator = iterator->next;
	}
	return (0);
}
