/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:27:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/18 00:53:37 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	remove_spaces()

static void	add_funct(t_general *gen, t_token **it)
{
	char	**matrix_c;
	char	operator;

	matrix_c = NULL;
	if ((*it)->content[ft_strlen((*it)->content) - 1] == ' ')
		(*it)->content[ft_strlen((*it)->content) - 1] = '\0';
	if (!check_valid_path((*it)->content) || cmd_searchlst((*it)->content))
		operator = 'F';
	else
		operator = 'N';
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

void	create_matrix(t_token **it, t_general *gen)
{
	gen->matrix = NULL;
	while (*it != NULL)
	{
		if (*it && (*it)->type == 'a')
			add_funct(gen, it);
		else if (*it)
			add_cmd(gen, it);
	}
}
