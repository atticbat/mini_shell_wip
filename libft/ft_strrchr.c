/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:51:03 by khatlas           #+#    #+#             */
/*   Updated: 2022/07/05 21:00:59 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;

	c = c % 128;
	len = ft_strlen(str);
	str = str + len;
	while (len + 1)
	{
		if (*str == c)
			return ((char *) str);
		len--;
		str--;
	}
	if (c == 0)
		return ((char *) str);
	return (0);
}
