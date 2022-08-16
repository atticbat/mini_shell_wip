/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:39:51 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/01 14:33:57 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	check_set(const char c, const char *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static size_t	find_from(const char *str, const char *set)
{
	size_t	i;

	i = 0;
	while (check_set(str[i], set) && str[i] != '\0')
		i++;
	return (i);
}

static size_t	find_to(const char *str, const char *set)
{
	size_t	i;

	i = ft_strlen(str) - 1;
	while (check_set(str[i], set) && i > 0)
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	from;
	size_t	to;
	char	*ptr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	from = find_from (s1, set);
	to = find_to (s1, set);
	if (from > to || (*set == 0 && *s1 == 0))
	{
		ptr = (char *) malloc (sizeof (char));
		if (!ptr)
			return (NULL);
		*ptr = '\0';
		return (ptr);
	}
	ptr = (char *) malloc ((to - from + 2) * sizeof (char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1 + from, to - from + 2);
	return (ptr);
}

//#include <stdio.h>
//
//int	main()
//{
//	char	*mstr = "         ";
//	char	*sub = " ";
//
//	printf("Start str: '%s', trim str:'%s'.\n", mstr, ft_strtrim(mstr, sub));
//	return (0);
//}
