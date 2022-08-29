/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:34:58 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/29 06:38:45 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_getenv(t_env *envp, char *search)
{
	t_env	*buffer;
    size_t  len;

    if (!envp || !search)
        return (NULL);
    len = ft_strlen(search);
	buffer = envp;
	while (buffer != NULL)
	{
        if (!ft_strncmp(buffer->name, search, (int) len) \
            && ft_strlen(buffer->name) == len)
            return (ft_strdup(buffer->content));
		buffer = buffer->next;
	}
    return (NULL);
}