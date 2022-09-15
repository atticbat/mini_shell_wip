/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:50:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/15 14:42:01 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (matrix != NULL)
	{
		if (ft_strchr(OPERATOR, matrix->operator))
			i++;
		matrix = matrix->next;
	}
	return (i);
}

static void	execute(char **arg, t_env *envp)
{
	char	cwd[PATH_MAX];
	char	*buffer;

	buffer = find_path_str(arg[0]);
	if (cmd_searchlst(arg[0]) == ECHO_CMD)
		ft_echo(arg);
	else if (cmd_searchlst(arg[0]) == CD_CMD)
		;
	else if (cmd_searchlst(arg[0]) == PWD_CMD)
		printf("%s\n", getcwd(cwd, PATH_MAX));
	else if (cmd_searchlst(arg[0]) == EXPORT_CMD)
		;
	else if (cmd_searchlst(arg[0]) == UNSET_CMD)
		;
	else if (cmd_searchlst(arg[0]) == ENV_CMD)
		ft_env(envp);
	else if (cmd_searchlst(arg[0]) == EXIT_CMD)
		;
	else if (buffer)
	{
		if (execv(buffer, arg) == -1)
			exit (-1);
	}
	exit (0);
}

static int	redirect_right(t_matrix *matrix)
{
	int	fd;

	if (matrix && matrix->operator == '>')
	{
		fd = open (matrix->next->matrix[0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (fd == -1)
			return (-1);
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
	else if (matrix && matrix->operator == '+')
	{
		fd = open (matrix->next->matrix[0], O_CREAT | O_WRONLY | O_APPEND, 0777);
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

int	find_pipes(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (matrix)
	{
		if (matrix->operator == '|')
			i++;
		matrix = matrix->next;
	}
	return (i);
}

static void	exe_heredoc(t_matrix *matrix, int pipe_count, int *pipefds, t_env *envp)
{
	pid_t	pid;
	int		i;

	pid = fork ();
	if (pid == 0)
	{
		i = 0;
		if (matrix && matrix->operator == '-')
		{
			if (matrix->next->matrix[0])
			{
				char	*buffer1;
				char	*buffer2;
				int		filetemp;

				filetemp = open (PATH_FILE_1, O_WRONLY \
				| O_CREAT | O_TRUNC, 0777);
				buffer2 = NULL;
				buffer1 = NULL;
				while (1)
				{
					write(1, HEREDOC, 9);
					buffer2 = get_next_line(0);
					if (!ft_strncmp(matrix->next->matrix[0], buffer2, \
					ft_strlen(matrix->next->matrix[0])))
						break ;
					buffer1 = expand_dquote(buffer2, envp, 0);
					free (buffer2);
					ft_putstr_fd(buffer1, filetemp);
					free (buffer1);
				}
				close (filetemp);
				filetemp = open (PATH_FILE_1, O_RDONLY, 0777);
				dup2(filetemp, STDIN_FILENO);
				close (filetemp);
			}
		}
		while (i < 2 * pipe_count)
		{
			close(pipefds[i]);
			i++;
		}
		exit (0);
	}
}

static void	exe_pipe(t_matrix *matrix, int pipe_count, int *pipefds, int j, t_env *envp)
{
	pid_t	pid;
	int		i;

	pid = fork ();
	if (pid == 0)
	{
		if (matrix->next && matrix->next->operator != '-' && matrix->next->operator != '<')
		{
			if (dup2(pipefds[j + 1], 1) == -1)
				printf("redirect stdout didnt work!\n");
		}
		if (j != 0)
		{
			if (dup2(pipefds[j - 2], 0) == -1)
				printf("redirect stdin didnt work!\n");
		}
		i = 0;
		if (matrix->next && matrix->next->operator == '-')
		{
			if (matrix->next->next->matrix[0])
			{
				char	*buffer1;
				char	*buffer2;
				int		filetemp;

				filetemp = open (PATH_FILE_1, O_WRONLY | O_CREAT | O_TRUNC, 0777);
				buffer2 = NULL;
				buffer1 = NULL;
				while (1)
				{
					write(1, HEREDOC, 9);
					buffer2 = get_next_line(0);
					if (!ft_strncmp(matrix->next->next->matrix[0], buffer2, ft_strlen(matrix->next->next->matrix[0])))
						break ;
                    if (!ft_strncmp(matrix->next->next->matrix[0] + 1, buffer2, ft_strlen(matrix->next->next->matrix[0] + 1)))
                        break ;
                    if (matrix->next->next->matrix[0][0] == '<')
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
		}
		if (matrix->next && matrix->next->operator == '<')
		{
			int fd;
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
		redirect_right(matrix->next);
		while (i < 2 * pipe_count) //close all fds in current child since we've already made our redirections
		{
			close(pipefds[i]);
			i++;
		}
		execute(matrix->matrix, envp);
	}
}

void	exe_cmd(t_matrix *matrix, int pipe_count, t_env **envp)
{
	int status;
	int i;
	int j;
	int *pipefds;

	pipefds = malloc (sizeof (int) * (pipe_count * 2));
	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			printf("piping fails\n");
			exit (-1);
		}
		i++;
	}
	j = 0;
	if (matrix && matrix->operator == '-')
	{
		exe_heredoc(matrix, pipe_count, pipefds, *envp);
		matrix = matrix->next;
		if (matrix)
			matrix = matrix->next;
	}
	while (matrix)
	{
		if (matrix->operator == '|')
		{
			matrix = matrix->next;
			continue ;
		}
		if (matrix->operator == '>' || matrix->operator == '+' || matrix->operator == '<' || matrix->operator == '-')
		{
			matrix = matrix->next;
			if (matrix)
				matrix = matrix->next;
			continue ;
		}
		exe_pipe (matrix, pipe_count, pipefds, j, *envp);
		if (cmd_searchlst(matrix->matrix[0]) == EXPORT_CMD)
			ft_export(matrix->matrix, envp);
		else if (cmd_searchlst(matrix->matrix[0]) == UNSET_CMD)
			ft_unset(matrix->matrix, envp);
		else if (cmd_searchlst(matrix->matrix[0]) == CD_CMD)
			ft_cd(matrix->matrix);
		else if (cmd_searchlst(matrix->matrix[0]) == EXIT_CMD)
			exit(0);
		if (matrix)
			matrix = matrix->next;
		j += 2;
	}
	i = 0;
	while (i < pipe_count * 2)
	{
		close (pipefds[i]);
		i++;
	}
	i = 0;
	while (i < pipe_count + 1)
	{
		wait (&status);
		i++;
	}
}
