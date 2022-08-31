/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:19:28 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/31 11:01:49 by khatlas          ###   ########.fr       */
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

static void	initialise(t_token **head, t_general *gen, char **envp)
{
	copy_envp(envp, gen);
	*head = NULL;
	gen->str = NULL;
	gen->error_no = 0;
	reset(gen, head, NULL);
	set_listeners();
}

static int	input_loop(t_token **head, t_general *gen)
{
    char		*inpt;

	while (1)
    {
		inpt = readline(PROMPT);
		if (!inpt || *inpt == EOF)
			handle_error(1, inpt, head, gen);
		if (check_empty(inpt))
			continue ;
		if (!*inpt)
		    continue ;
		add_history(inpt);
		if (handle_error(find_token(inpt, head, gen), inpt, head, gen))
			continue ;
		if (handle_error(expand_variable(head, gen), inpt, head, gen))
			continue ;
		if (handle_error(parse_function(head, gen), inpt, head, gen))
			continue ;
		reset(gen, head, inpt);
    }
	free_all(inpt, head, gen);
	return (0);
}

int main (int argc, char **argv, char **envp)
{
	t_token		*head;
	t_general	gen;

	(void) argc;
	(void) argv;
	initialise(&head, &gen, envp);
	input_loop(&head, &gen);
    return (0);
}
