/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:24:51 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/17 12:47:02 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;

	ptr = (const unsigned char *) s;
	while (n)
	{
		if (*ptr == (unsigned char) c)
			return ((void *)&*ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
