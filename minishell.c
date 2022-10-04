/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:19:28 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/04 03:57:48 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_empty(char *in)
{
	int	i;

	i = 0;
	while (in[i] != '\0' && ft_strchr(WHITESPACE, in[i]))
		i++;
	if (i == 0)
		return (0);
	if (in[i] == '\0')
		return (1);
	return (0);
}

static void	initialise(t_general *gen, char **envp)
{
	copy_envp(envp, gen);
	gen->tokens = NULL;
	gen->matrix = NULL;
	gen->in = NULL;
	gen->error_no = 0;
	set_listeners();
}

static void	input_loop(t_general *gen)
{
	while (1)
	{
		reset(gen);
		gen->in = readline(PROMPT);
		if (handle_error((!gen->in || gen->in[0] == EOF) * -1, gen))
			break ;
		if (check_empty(gen->in) || !gen->in[0])
		{
			free (gen->in);
			continue ;
		}
		add_history(gen->in);
		if (handle_error(find_token(gen), gen))
			continue ;
		if (handle_error(builtin_executions(gen), gen))
			break ;
		if (handle_error(expand_variable(gen), gen))
			continue ;
		if (handle_error(parse_function(gen), gen))
			continue ;
		if (handle_error(execute_prep(gen), gen))
			continue ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_general	gen;

	if (!envp)
	{
		write(2, "Environment not found. Aborting\n", 32);
		return (-1);
	}
	(void) argc;
	(void) argv;
	initialise (&gen, envp);
	input_loop (&gen);
	free_all(&gen);
	remove_files();
	return (0);
}
