/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:45:44 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/17 12:46:41 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	if (size > SIZE_MAX / count)
		return (NULL);
	ptr = (void *) malloc (size * count);
	if (!ptr)
		return (NULL);
	ft_bzero (ptr, size * count);
	return (ptr);
}
