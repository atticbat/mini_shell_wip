/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:04:32 by khatlas           #+#    #+#             */
/*   Updated: 2022/07/05 21:00:25 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static const char	*concat(char *d, const char *s, size_t i)
{
	while (*s != '\0')
	{
		if (i > 1)
		{
			*d = *s;
			d++;
			i--;
		}
		s++;
	}
	*d = '\0';
	return (s);
}

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;
	size_t		len;

	d = dst;
	s = src;
	i = n;
	while (*d != '\0' && i > 0)
	{
		d++;
		i--;
	}
	len = d - dst;
	i = n - len;
	if (i == 0)
		return (len + ft_strlen(s));
	s = concat (d, s, i);
	return (len + (s - src));
}
