/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:29:17 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/05 18:21:04 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gnl_strdup(char *src)
{
	size_t	len;
	int		i;
	char	*dest;

	len = ft_strlen(src);
	dest = malloc(len + 1);
	i = 0;
	if (dest == 0)
		return (0);
	else
	{
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		return (dest);
	}
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*buffer;
	size_t	c2;
	size_t	c1;

	if(!s1)
		s1 = gnl_strdup("");
	if (!s1 || !s2)
		return (0);
	c2 = gnl_strlen(s2);
	c1 = gnl_strlen(s1);
	buffer = malloc(sizeof(char) * (c1 + c2 +1));
	if (!buffer)
		return (NULL);
	c1 = 0;
	c2 = 0;
	while (s1[c1] != '\0')
	{
		buffer[c1] = s1[c1];
		c1++;
	}
	c1 = gnl_strlen(s1);
	while (s2[c2] != '\0')
	{
		buffer[c1] = s2[c2];
		c1++;
		c2++;
	}
	buffer[c1] = '\0';
	free(s1);
	return (buffer);
}

char	*gnl_strchr(char *s, int c)
{
	int	counter;
	int	len;

	counter = 0;
	if (!s)
		return ((char *)&s[counter]);
	len = (int)gnl_strlen(s);
	while (counter < len + 1)
	{
		if (*(s + counter) == (char)c)
			return ((char *)s + counter);
		counter ++;
	}
	return (NULL);
}


size_t	gnl_strlen (char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
		count ++;
	return (count);
}
