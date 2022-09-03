/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:18:32 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/03 16:31:21 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_all_token(t_token *lst)
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

void    print_all_matrix(t_matrix *lst)
{
    t_matrix	*buffer;
	int			i;

	buffer = lst;
	while (buffer != NULL)
	{
        printf("buffer; cmd: %s, matrix:\t", buffer->cmd);
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