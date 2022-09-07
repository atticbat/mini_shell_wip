/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:19:28 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/07 16:48:35 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_empty(char *in)
{
    int i;

    i = 0;
    while (in[i] != '\0' && ft_strchr(WHITESPACE, in[i]))
        i++;
    if (i == 0)
        return (0);
    if (in[i] == '\0')
	{
		free (in);
        return (1);
	}
    return (0);
}

static void	initialise(t_general *gen, char **envp)
{
	copy_envp(envp, gen);
	gen->tokens = NULL;
	gen->matrix = NULL;
	gen->error_no = 0;
	env_find(gen, "PATH");
	reset(gen);
	set_listeners();
}

static int	input_loop(t_general *gen)
{
	while (1)
    {
		gen->in = readline(PROMPT);
		if (!gen->in || gen->in[0] == EOF)
			handle_error(1, gen);
		if (check_empty(gen->in) || !gen->in[0])
			continue ;
		add_history(gen->in);
		if (handle_error(find_token(gen), gen))
			continue ;
		if (handle_error(expand_variable(gen), gen))
			continue ;
		if (handle_error(parse_function(gen), gen))
			continue ;
		if (handle_error(execute_cases(gen), gen))
			continue;
		reset(gen);
    }
	free_all(gen);
	return (0);
}

int main (int argc, char **argv, char **envp)
{
	t_general	gen;

	(void) argc;
	(void) argv;
	initialise(&gen, envp);
	input_loop(&gen);
    return (0);
}
