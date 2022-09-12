/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:26:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/12 15:31:49 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2)
{
	unsigned int	len;
	char			*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (s1[0] == '\0' && s2[0] == '\0')
		len++;
	ptr = (char *) malloc ((len) * sizeof (char));
	if (!ptr)
		return (0);
	ft_strlcpy (ptr, s1, len);
	ft_strlcat (ptr, s2, len);
	free (s1);
	free (s2);
	return (ptr);
}
