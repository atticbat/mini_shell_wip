/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:09:17 by khatlas           #+#    #+#             */
/*   Updated: 2022/07/05 20:54:58 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	long int	total;
	int			negate;

	total = 0;
	negate = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negate = negate * -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		total = total * 10 + (*str - 48);
		str++;
		if (total * negate > 2147483647)
			return (-1);
		if (total * negate < -2147483648)
			return (0);
	}
	return ((int) total * negate);
}
