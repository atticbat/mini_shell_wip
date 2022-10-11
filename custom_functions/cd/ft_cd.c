/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:05:17 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/11 18:45:52 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_home_path(char cwd[PATH_MAX])
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buffer = NULL;
	while (cwd[i] != '\0')
	{
		if (cwd[i] == '/')
			j++;
		if (j == 3)
		{
			buffer = ft_substr(cwd, 0, i + 1);
			break ;
		}
		i++;
	}
	return (buffer);
}

static int	cd_no_arg(void)
{
	char	cwd[PATH_MAX];
	char	*buffer;

	getcwd(cwd, PATH_MAX);
	buffer = extract_home_path(cwd);
	if (chdir(buffer) != 0)
		return (-1);
	if (buffer)
		free (buffer);
	return (0);
}

static void	cd_extra(t_general *gen, char *cwd)
{
	ft_export_replace_two(&gen->envp, cwd, "OLDPWD");
	getcwd(cwd, PATH_MAX);
	ft_export_replace_two(&gen->envp, cwd, "PWD");
}

int	ft_cd(t_general *gen)
{
	t_token	*it;
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	it = gen->tokens;
	if (!it)
		return (DEFAULT_ERR);
	it = it->next;
	if (it && it->content && it->content[ft_strlen(it->content) - 1] == ' ')
		it->content[ft_strlen(it->content) - 1] = '\0';
	if (!it || !it->content)
	{
		if (cd_no_arg())
		{
			perror("chdir() failed");
			return (NOFILE_ERR);
		}
	}
	else if (chdir(it->content) != 0)
	{
		perror("chdir() failed");
		return (NOFILE_ERR);
	}
	cd_extra(gen, cwd);
	return (0);
}
