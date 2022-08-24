/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:18:32 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/18 10:00:03 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_all(t_token *lst)
{
    t_token	*buffer;
	int		i;

	buffer = lst;
	i = 0;
	while (buffer != NULL)
	{
        printf("buffer; type: %c, contents: '%s'\n", buffer->type, \
			buffer->content);
		buffer = buffer->next;
		i++;
	}
}