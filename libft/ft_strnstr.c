/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:10:15 by khatlas           #+#    #+#             */
/*   Updated: 2022/07/05 21:00:54 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t n)
{
	size_t	len;

	if (sub[0] == '\0')
		return ((char *) str);
	len = ft_strlen(sub);
	if (len > ft_strlen(str))
		return (0);
	while (n)
	{
		if (n < len)
			break ;
		if (ft_strncmp (str, sub, len) == 0)
			return ((char *) str);
		str++;
		n--;
	}
	return (0);
}
