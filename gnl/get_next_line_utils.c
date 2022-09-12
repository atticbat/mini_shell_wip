/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:29:17 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/12 13:50:11 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static void	*gnl_memcpy(void *dst, const void *src, size_t n)
{
	char		*dstptr;
	const char	*srcptr;

	if (!dst && !src)
		return (NULL);
	dstptr = (char *) dst;
	srcptr = (const char *) src;
	while (n)
	{
		*dstptr = *srcptr;
		dstptr++;
		srcptr++;
		n--;
	}
	return (dst);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	unsigned int	len1;
	unsigned int	len2;
	unsigned int	to_malloc;
	char			*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	to_malloc = len1 + len2 + 1;
	if (s1[0] == '\0' && s2[0] == '\0')
		to_malloc++;
	ptr = (char *) malloc ((to_malloc) * sizeof (char));
	if (!ptr)
		return (NULL);
	gnl_memcpy (ptr, s1, len1);
	gnl_memcpy (ptr + len1, s2, len2);
	ptr[len1 + len2] = '\0';
	return (ptr);
}

char	*gnl_strdup(const char *str)
{
	size_t	l;
	char	*ptr;
	size_t	i;

	if (!str)
		return (NULL);
	l = gnl_strlen(str);
	ptr = (char *) malloc (sizeof(char) * (l + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < l)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (NULL);
	if (gnl_strlen(s) < start)
	{
		ptr = (char *) malloc (sizeof (char));
		if (!ptr)
			return (NULL);
		*ptr = '\0';
		return (ptr);
	}
	if (gnl_strlen(s) - start > len)
		i = len + 1;
	else
		i = gnl_strlen(s) - start + 2;
	ptr = (char *) malloc ((i) * sizeof (char));
	if (!ptr)
		return (NULL);
	gnl_memcpy(ptr, s + start, i - 1);
	ptr[i - 1] = '\0';
	return (ptr);
}
