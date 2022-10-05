/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:50:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/05 18:02:14 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_operators(t_matrix *matrix, char *dataset)
{
	t_matrix	*it;
	int			i;

	it = matrix;
	i = 0;
	while (it != NULL)
	{
		if (ft_strchr(dataset, it->operator))
			i++;
		it = it->next;
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

	if (!check_file(arg[0]) && !ft_strncmp(arg[0], "./", 2))
		if (execv(arg[0], arg) == -1)
			exit (-1);
	buffer = find_path_str(arg[0]);
	if (cmd_searchlst(arg[0]) == ECHO_CMD)
		ft_echo(arg);
	else if (cmd_searchlst(arg[0]) == CD_CMD \
		|| cmd_searchlst(arg[0]) == UNSET_CMD \
		|| cmd_searchlst(arg[0]) == EXIT_CMD \
		|| (cmd_searchlst(arg[0]) == EXPORT_CMD && arg[1]))
		;
	else if (cmd_searchlst(arg[0]) == PWD_CMD)
		printf("%s\n", getcwd(cwd, PATH_MAX));
	else if (cmd_searchlst(arg[0]) == ENV_CMD && !arg[1])
		ft_env(envp);
	else if (cmd_searchlst(arg[0]) == EXPORT_CMD && !arg[1])
		export_print_vars(envp);
	else if (buffer)
	{
		if (execv(buffer, arg) == -1)
			exit (-1);
	}
	if (!cmd_searchlst(arg[0]))
		perror(arg[0]);
	exit (0);
}
