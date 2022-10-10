/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:27:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/10 04:14:20 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_funct(t_general *gen, t_token **it)
{
	char	**matrix_c;
	char	operator;

	matrix_c = NULL;
	if ((*it)->content[ft_strlen((*it)->content) - 1] == ' ')
		(*it)->content[ft_strlen((*it)->content) - 1] = '\0';
	if (!check_env((*it)->content) || cmd_searchlst((*it)->content) || \
		(!check_file((*it)->content) && ((*it)->content[0] == '/' || \
		((*it)->content[1] == '/' ))))
		operator = 'F';
	else
	{
		operator = 'N';
		gen->error_no = 127;
	}
	matrix_c = extract_matrix(it);
	if (!matrix_c)
		return ;
	matrix_add_back(&gen->matrix, matrix_new(operator, matrix_c));
}

static void	add_cmd(t_general *gen, t_token **it)
{
	char	**matrix_c;
	char	operator;

	operator = (*it)->type;
	matrix_c = malloc (sizeof(char *) * 2);
	matrix_c[0] = ft_strdup("");
	matrix_c[1] = NULL;
	matrix_add_back(&gen->matrix, matrix_new(operator, matrix_c));
	*it = (*it)->next;
}

static t_token	*get_third(t_token *tokens)
{
	t_token	*it;
	int		i;

	it = tokens;
	i = 2;
	while (it != NULL && i)
	{
		it = it->next;
		i--;
	}
	if (i || !it || it->content == NULL)
		return (NULL);
	return (it);
}

static void	add_rearranged_redir(t_general *gen, t_token **it)
{
	t_token	*buffer;
	char	**matrix_c;

	buffer = get_third(*it);
	if (!buffer)
		return ;
	add_funct(gen, &buffer);
	add_cmd(gen, it);
	matrix_c = malloc (sizeof(char *) * 2);
	matrix_c[0] = ft_strdup((*it)->content);
	if (matrix_c[0][ft_strlen(matrix_c[0]) - 1] == ' ')
		matrix_c[0][ft_strlen(matrix_c[0]) - 1] = '\0';
	matrix_c[1] = NULL;
	matrix_add_back(&gen->matrix, matrix_new('N', matrix_c));
	*it = (*it)->next;
	*it = (*it)->next;
}

void	create_matrix(t_token **it, t_general *gen)
{
	int	flag;

	flag = 1;
	gen->matrix = NULL;
	while (*it != NULL)
	{
		if (*it && ((*it)->type == '<' || (*it)->type == '-') && flag == 1)
		{
			skip_multiple_ins(it, gen);
			add_rearranged_redir(gen, it);
		}
		if (*it && (*it)->type == 'a')
		{
			add_funct(gen, it);
			flag = 0;
		}
		else if (*it)
		{
			add_cmd(gen, it);
			flag = 1;
		}
	}
}
