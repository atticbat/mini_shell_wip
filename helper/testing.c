/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:18:32 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/12 13:52:31 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_all_token(t_token *lst)
{
	t_token	*buffer;

	buffer = lst;
	while (buffer != NULL)
	{
		printf("buffer; type: %c, contents: '%s'\n", buffer->type, \
			buffer->content);
		buffer = buffer->next;
	}
}

void	print_all_matrix(t_matrix *lst)
{
	t_matrix	*buffer;
	int			i;

	buffer = lst;
	while (buffer != NULL)
	{
		printf("operator: %c, matrix:\t", buffer->operator);
		i = 0;
		while (buffer->matrix[i] != NULL)
		{
			printf("'%s',\t", buffer->matrix[i]);
			i++;
		}
		printf("\n");
		buffer = buffer->next;
	}
}

void	print_execute(t_execute lst)
{
	int	i;

	i = 0;
	if (lst.arg1 == NULL)
		return ;
	while (lst.arg1[i] != NULL)
		printf("arg1: %s \t", lst.arg1[i++]);
	i = 0;
	printf("\n");
	if (lst.arg2 == NULL)
		return ;
	while (lst.arg2[i] != NULL)
		printf("arg2: %s\t", lst.arg2[i++]);
	printf("\noperator: %c", lst.operator);
	printf("\n");
}
