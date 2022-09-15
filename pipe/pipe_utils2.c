/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:48:47 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/16 01:00:19 by khatlas          ###   ########.fr       */
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

void	execute(char **arg, t_env *envp)
{
	char	cwd[PATH_MAX];
	char	*buffer;

	buffer = find_path_str(arg[0]);
	if (cmd_searchlst(arg[0]) == ECHO_CMD)
		ft_echo(arg);
	else if (cmd_searchlst(arg[0]) == CD_CMD \
		|| cmd_searchlst(arg[0]) == EXPORT_CMD \
		|| cmd_searchlst(arg[0]) == UNSET_CMD \
		|| cmd_searchlst(arg[0]) == EXIT_CMD)
		;
	else if (cmd_searchlst(arg[0]) == PWD_CMD)
		printf("%s\n", getcwd(cwd, PATH_MAX));
	else if (cmd_searchlst(arg[0]) == ENV_CMD)
		ft_env(envp);
	else if (buffer)
	{
		if (execv(buffer, arg) == -1)
			exit (-1);
	}
	exit (0);
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
