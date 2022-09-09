/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:29:17 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/08 15:35:10 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*gnl_strdup(char *src)
// {
// 	size_t	len;
// 	int		i;
// 	char	*dest;

// 	len = gnl_strlen(src);
// 	dest = malloc(len + 1);
// 	i = 0;
// 	if (dest == 0)
// 		return (0);
// 	else
// 	{
// 		while (src[i])
// 		{
// 			dest[i] = src[i];
// 			i++;
// 		}
// 		dest[i] = '\0';
// 		return (dest);
// 	}
// }

// char	*gnl_strjoin(char *s1, char *s2)
// {
// 	char	*buffer;
// 	size_t	c2;
// 	size_t	c1;

// 	if(!s1)
// 		s1 = gnl_strdup("");
// 	if (!s1 || !s2)
// 		return (0);
// 	c2 = gnl_strlen(s2);
// 	c1 = gnl_strlen(s1);
// 	buffer = malloc(sizeof(char) * (c1 + c2 +1));
// 	if (!buffer)
// 		return (NULL);
// 	c1 = 0;
// 	c2 = 0;
// 	while (s1[c1] != '\0')
// 	{
// 		buffer[c1] = s1[c1];
// 		c1++;
// 	}
// 	c1 = gnl_strlen(s1);
// 	while (s2[c2] != '\0')
// 	{
// 		buffer[c1] = s2[c2];
// 		c1++;
// 		c2++;
// 	}
// 	buffer[c1] = '\0';
// 	free(s1);
// 	return (buffer);
// }

// char	*gnl_strchr(char *s, int c)
// {
// 	int	counter;
// 	int	len;

// 	counter = 0;
// 	if (!s)
// 		return ((char *)&s[counter]);
// 	len = (int)gnl_strlen(s);
// 	while (counter < len + 1)
// 	{
// 		if (*(s + counter) == (char)c)
// 			return ((char *)s + counter);
// 		counter ++;
// 	}
// 	return (NULL);
// }


// size_t	gnl_strlen (char *str)
// {
// 	size_t	count;

// 	count = 0;
// 	while (str[count] != '\0')
// 		count ++;
// 	return (count);
// }


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