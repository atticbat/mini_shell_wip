/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:24:55 by khatlas           #+#    #+#             */
/*   Updated: 2022/07/05 21:00:19 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (ptr);
}

//#include <stdio.h>
//
//int	main()
//{
//	char	*s1 = "abcdefghijklmno";
//	char	*s2 = "pqrstuvwxyz";
//	printf("Strings: %s, %s, together: %s\n", s1, s2, ft_strjoin(s1, s2));
//	return (0);
//}
