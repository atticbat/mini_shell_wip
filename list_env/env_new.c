/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:24:17 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/17 12:38:32 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(char *name, char *content, int user_set)
{
	t_env	*result;

	result = malloc(sizeof(t_env));
	if (!result)
		return (NULL);
	result->name = name;
	result->content = content;
	result->user_set = user_set;
	result->next = NULL;
	return (result);
}
