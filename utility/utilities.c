/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:18:57 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/09 06:35:45 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset(t_general *gen)
{
	gen->last_return = gen->error_no;
	gen->error_no = 0;
	gen->to = 0;
	gen->from = 0;
	gen->flag = 0;
	gen->builtin_flag = 0;
	gen->cmd_flag = 1;
	if (gen->tokens)
		token_clear(&gen->tokens, free);
	if (gen->matrix)
		matrix_clear(&gen->matrix, free);
	gen->tokens = NULL;
	gen->matrix = NULL;
}

void	free_all(t_general *gen)
{
	reset(gen);
	env_clear(&gen->envp, free);
	rl_clear_history();
}

static void	erase_temp(char *buff)
{
	char	**matrix;
	int		tempfile;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		matrix = malloc (sizeof (char *) * 3);
		matrix[0] = ft_strdup("rm -f");
		matrix[1] = buff;
		matrix[2] = NULL;
		tempfile = open (buff, O_CREAT, 0777);
		close (tempfile);
		execv("/bin/rm", matrix);
	}
	wait (&status);
}

void	remove_files(void)
{
	int		i;
	char	*buffer;
	char	*buff2;

	i = 0;
	buffer = NULL;
	buff2 = NULL;
	while (1)
	{
		i++;
		buff2 = ft_itoa(i);
		buffer = ft_strjoin(PATH_FILE_1, buff2);
		if (!check_file(buffer))
			erase_temp(buffer);
		else
		{
			free (buffer);
			free (buff2);
			break ;
		}
		free (buffer);
		free (buff2);
	}
}
