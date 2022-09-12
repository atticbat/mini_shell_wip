/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 20:15:55 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/12 13:38:03 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_pwd(char *buff)
{
	int		size_buff;
	char	*path;

	path = NULL;
	size_buff = ft_strlen(buff);
	path = getcwd(buff, size_buff);
	return (path);
}
