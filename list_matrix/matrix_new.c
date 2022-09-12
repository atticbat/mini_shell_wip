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

t_matrix	*matrix_new(char operator, char **matrix)
{
	t_matrix	*result;

	result = malloc(sizeof(t_matrix));
	if (!result)
		return (NULL);
	result->operator = operator;
	result->matrix = matrix;
	result->next = NULL;
	return (result);
}
