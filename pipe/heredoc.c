/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:09:53 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/04 02:09:03 by khatlas          ###   ########.fr       */
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

void	ft_heredoc(t_matrix *matrix, t_env *envp, int heredoc_n)
{
	char	*buffer1;
	char	*buffer2;
	int		filetemp;

	char	*name;
	buffer1 = ft_itoa(heredoc_n); 
	name = ft_strjoin(PATH_FILE_1, buffer1);
	free (buffer1);
	filetemp = open (name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
	free (name);
	// filetemp = open (name, O_RDONLY, 0777);
	// dup2(filetemp, STDIN_FILENO);
	// close (filetemp);
}
//cuando entra el numero de heredoc se realiza un fork para poder llamar la senal
// luego realiza una operacion de matrix
void	exe_heredoc(t_matrix *matrix, t_execute *exevars, t_env *envp, int heredoc_n)
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
				ft_heredoc(matrix, envp, heredoc_n);
		}
		exit (0);
	}
	wait (&status);
	// while (i < 2 * exevars->pipe_count)
	// {
	// 	close(exevars->pipefds[i]);
	// 	i++;
	// }
}
