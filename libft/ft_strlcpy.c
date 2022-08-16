/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:13:18 by khatlas           #+#    #+#             */
/*   Updated: 2022/07/05 21:00:30 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	len;
	void	*vdst;
	void	*vsrc;

	len = ft_strlen (src);
	if (!n)
		return (len);
	vdst = (void *) dst;
	vsrc = (void *) src;
	if (len + 1 < n)
		ft_memcpy (vdst, vsrc, len + 1);
	else if (len != 0)
	{
		ft_memcpy (vdst, vsrc, n - 1);
		dst[n - 1] = '\0';
	}
	return (len);
}
