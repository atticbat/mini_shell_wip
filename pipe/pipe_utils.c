/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:50:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/16 00:52:09 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_input_stream(void)
{
	char	*final;

	final = NULL;
	write(1, HEREDOC, 9);
	final = get_next_line(0);
	if (!final)
		write(1, "\n", 1);
	return (final);
}

void	ft_heredoc(t_matrix *matrix, t_env *envp)
{
	char	*buffer1;
	char	*buffer2;
	int		filetemp;

	filetemp = open (PATH_FILE_1, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		buffer2 = heredoc_input_stream();
		if (!ft_strncmp(matrix->next->matrix[0] + 1, buffer2, \
			ft_strlen(matrix->next->matrix[0] + 1)) \
			&& ft_strlen(matrix->next->matrix[0] + 1) == ft_strlen(buffer2) - 1)
			break ;
		if (matrix->next->matrix[0][0] == '<')
			buffer1 = expand_dquote(buffer2, envp, 0);
		else
			buffer1 = ft_strdup(buffer2);
		free (buffer2);
		ft_putstr_fd(buffer1, filetemp);
		free (buffer1);
	}
	close (filetemp);
	filetemp = open (PATH_FILE_1, O_RDONLY, 0777);
	dup2(filetemp, STDIN_FILENO);
	close (filetemp);
}

void	exe_heredoc(t_matrix *matrix, t_execute *exevars, t_env *envp)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork ();
	if (pid == 0)
	{
		if (matrix && matrix->operator == '-')
		{
			if (matrix->next->matrix[0])
				ft_heredoc(matrix, envp);
		}
		while (i < 2 * exevars->pipe_count)
		{
			close(exevars->pipefds[i]);
			i++;
		}
		exit (0);
	}
}

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

static void	child_redirections(t_matrix *matrix, t_execute *exevars, \
	t_env *envp)
{
	if (matrix->next && matrix->next->operator != '-' \
	&& matrix->next->operator != '<')
		if (dup2(exevars->pipefds[exevars->index + 1], 1) == -1)
			printf("redirect stdout didnt work!\n");
	if (exevars->index != 0)
		if (dup2(exevars->pipefds[exevars->index - 2], 0) == -1)
			printf("redirect stdin didnt work!\n");
	if (matrix->next && matrix->next->operator == '-')
		if (matrix->next->next->matrix[0])
			ft_heredoc(matrix->next, envp);
	if (matrix->next && matrix->next->operator == '<')
		redirect_left(matrix);
	redirect_right(matrix->next);
}

void	exe_pipe(t_matrix *matrix, t_execute *exevars, t_env *envp)
{
	pid_t	pid;
	int		i;

	pid = fork ();
	if (pid == 0)
	{
		child_redirections(matrix, exevars, envp);
		i = 0;
		while (i < 2 * exevars->pipe_count)
		{
			close(exevars->pipefds[i]);
			i++;
		}
		execute(matrix->matrix, envp);
	}
}
