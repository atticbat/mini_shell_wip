/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:09:53 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/10 03:47:02 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_input_stream(void)
{
	char	*final;

	final = NULL;
	write(1, HEREDOC, 2);
	final = get_next_line(0);
	if (!final)
		write(1, "\n", 1);
	return (final);
}

static char	*get_heredoc_line(char *str, t_env *envp)
{
	char	*buffer1;
	char	*buffer2;

	buffer1 = NULL;
	buffer2 = heredoc_input_stream();
	if (!ft_strncmp(str + 1, buffer2, \
		ft_strlen(str + 1)) && ft_strlen(\
		str + 1) == ft_strlen(buffer2) - 1)
		return (NULL);
	if (str[0] == '<')
		buffer1 = expand_dquote(buffer2, envp, 0);
	else
		buffer1 = ft_strdup(buffer2);
	free (buffer2);
	return (buffer1);
}

void	ft_heredoc(char *str, t_env *envp, int heredoc_n)
{
	char	*buffer1;
	int		filetemp;
	char	*name;

	buffer1 = ft_itoa(heredoc_n);
	name = ft_strjoin(PATH_FILE_1, buffer1);
	free (buffer1);
	filetemp = open (name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		buffer1 = get_heredoc_line(str, envp);
		if (!buffer1)
			break ;
		ft_putstr_fd(buffer1, filetemp);
		free (buffer1);
	}
	close (filetemp);
	free (name);
}

void	exe_heredoc(t_matrix *matrix, t_execute *exevars, t_env *envp, \
	int heredoc_n)
{
	int		i;
	int		status;
	pid_t	pid;

	(void)exevars;
	i = 0;
	pid = fork ();
	if (pid == 0)
	{
		signal(SIGINT, interrupt_handler_child);
		if (matrix && matrix->operator == '-')
		{
			if (matrix->next->matrix[0])
				ft_heredoc(matrix->next->matrix[0], envp, heredoc_n);
		}
		exit (0);
	}
	waitpid (pid, &status, 0);
}

void	read_heredoc(t_execute *exevars)
{
	int		fd;
	char	*buffer;

	buffer = ft_strjoinfree(ft_strdup(PATH_FILE_1), \
		ft_itoa(exevars->heredoc_n));
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
