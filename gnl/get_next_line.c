/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:00:29 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/16 00:33:32 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*store_append(char *store, char *buff, char **hold)
{
	if (store == NULL)
		store = gnl_strdup (buff);
	else
	{
		*hold = gnl_strjoin(store, buff);
		free (store);
		return (*hold);
	}
	return (store);
}

static char	*free_gnl(char *hold)
{
	if (hold)
		free (hold);
	return (NULL);
}

static char	*generate_string(char *store, char **out, char **hold, int len)
{
	if (store[len] == '\n')
	{
		*out = gnl_substr(store, 0, len + 1);
		*hold = gnl_strdup(&(store[len + 1]));
		free (store);
		return (*hold);
	}
	else
	{
		if (store[0] == '\0')
			store = NULL;
		free (*hold);
		*out = gnl_strdup(store);
		return (NULL);
	}
}

static char	*gnl_strchr(const char *str, int c)
{
	c = c % 128;
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return ((char *) str);
		str++;
	}
	if (c == 0)
		return ((char *) str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_static	ctnr;
	char			*hold;
	char			*out;
	int				len;

	hold = NULL;
	out = NULL;
	len = 1;
	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1024)
		return (NULL);
	while (len > 0 && !(gnl_strchr(ctnr.store, '\n')))
	{
		len = read (fd, ctnr.buff, BUFFER_SIZE);
		if (*(ctnr.buff) == '\0' || len == -1)
			return (free_gnl(hold));
		(ctnr.buff)[len] = '\0';
		ctnr.store = store_append(ctnr.store, ctnr.buff, &hold);
	}
	len = 0;
	while ((ctnr.store)[len] != '\n' && (ctnr.store)[len] != '\0')
		len++;
	ctnr.store = generate_string(ctnr.store, &out, &hold, len);
	return (out);
}
