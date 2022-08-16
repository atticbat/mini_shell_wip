/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:59:06 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/01 14:33:08 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	make_move(char *ptrdst, const char *ptrsrc, size_t n)
{
	if (ptrsrc > ptrdst)
	{
		while (n)
		{
			*ptrdst = *ptrsrc;
			n--;
			ptrdst++;
			ptrsrc++;
		}
	}
	else
	{
		ptrdst += (n - 1);
		ptrsrc += (n - 1);
		while (n)
		{
			*ptrdst = *ptrsrc;
			ptrdst--;
			ptrsrc--;
			n--;
		}
	}
}

void	*ft_memmove(void *dst, void *src, size_t n)
{
	char		*ptrdst;
	const char	*ptrsrc;

	ptrdst = (char *) dst;
	ptrsrc = (const char *) src;
	if ((!dst && !src))
		return (dst);
	make_move(ptrdst, ptrsrc, n);
	return (dst);
}
