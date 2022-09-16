/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:10:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/16 20:11:25 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_left(t_matrix *matrix)
{	
	int	fd;

	fd = open (matrix->next->next->matrix[0], O_CREAT | O_RDONLY, 0777);
	if (fd == -1)
	{
		printf("error file not found");
		exit (-1);
	}
	if (matrix->next && matrix->next->next && matrix->next->next->next)
		redirect_right(matrix->next->next->next);
	dup2(fd, STDIN_FILENO);
	close (fd);
}

int	redirect_right(t_matrix *matrix)
{
	int	fd;

	if (matrix && matrix->operator == '>')
	{
		fd = open(matrix->next->matrix[0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (fd == -1)
			return (-1);
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
	else if (matrix && matrix->operator == '+')
	{
		fd = open(matrix->next->matrix[0], O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (fd == -1)
			return (-1);
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
	else
		return (-1);
	close(fd);
	return (0);
}
