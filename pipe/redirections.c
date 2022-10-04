/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:10:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/04 06:10:27 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc(t_execute *exevars)
{
	int	fd;
	char	*buffer;

	buffer = ft_strjoinfree(ft_strdup(PATH_FILE_1), ft_itoa(exevars->heredoc_n));
	fd = open (buffer, O_RDONLY, 0777);
	if (fd == -1)
	{
		perror (buffer);
		free (buffer);
		exit (NOFILE_ERR);
	}
	free (buffer);
	dup2(fd, READ_END);
	close (fd);
}

static void	read_file(t_matrix **it)
{
	int	fd;

	fd = open ((*it)->next->next->matrix[0], O_RDONLY, 0777);
	if (fd == -1)
	{
		perror ((*it)->next->next->matrix[0]);
		exit (NOFILE_ERR);
	}
	dup2(fd, READ_END);
	close (fd);
}

static void	append(t_matrix **it)
{
	int	fd;

	fd = open ((*it)->next->next->matrix[0], O_APPEND | O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
	{
		perror ((*it)->next->next->matrix[0]);
		exit (NOFILE_ERR);
	}
	dup2(fd, WRITE_END);
	close (fd);	
}

static void	overwrite(t_matrix **it)
{
	int	fd;

	fd = open ((*it)->next->next->matrix[0], O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
	{
		perror ((*it)->next->next->matrix[0]);
		exit (NOFILE_ERR);
	}
	dup2(fd, WRITE_END);
	close (fd);	
}

void	redirect(t_matrix **it, t_execute *exevars)
{
	if (*it && (*it)->next && (*it)->next->next)
	{
		if ((*it)->next->operator == '-')
			read_heredoc(exevars);
		if ((*it)->next->operator == '<')
			read_file(it);
		else if ((*it)->next->operator == '+')
			append(it);
		else if ((*it)->next->operator == '>')
			overwrite(it);
	}
	else if (*it && (*it)->next)
		exit (SYNTAX_ERR);	
}
