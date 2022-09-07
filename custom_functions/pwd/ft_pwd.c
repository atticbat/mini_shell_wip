/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 20:15:55 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/07 17:31:29 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_pwd(char *buff)
{
	int size_buff;
	char *path;

	path = NULL;
	size_buff = ft_strlen(buff);
	path = getcwd(buff, size_buff);
	return (path);
}