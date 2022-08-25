/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:10:15 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/25 10:26:17 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, char *sub, size_t n)
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
