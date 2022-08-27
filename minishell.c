/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:19:28 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/28 00:33:24 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void interrupt_handler(int signum)
{
    (void) signum;
    write (1, "\n", 1);
    rl_free_line_state();
    rl_on_new_line();
	rl_replace_line("", 0);
    rl_redisplay();
}

static void	do_nothing_handler(int signum)
{
	(void) signum;
	rl_free_line_state();
    rl_on_new_line();
    rl_redisplay();
}

static int	check_empty(char *in)
{
    int i;

    i = 0;
    while (in[i] != '\0' && ft_strchr(WHITESPACE, in[i]))
        i++;
    if (i == 0)
        return (0);
    if (in[i] == '\0')
        return (1);
    return (0);
}

int main (int argc, char **argv, char **envp)
{
	t_token		*head;
    char		*inpt;
	t_general	gen;

	(void) argc;
	(void) argv;
	gen.envp = copy_envp(envp);
	head = NULL;
	inpt = NULL;
	reset(&gen, &head, inpt);
    signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, do_nothing_handler);
    while (1)
    {
		inpt = readline(PROMPT);
		if (!inpt || *inpt == EOF)
		{
			free (inpt);
			break ;
		}
		if (check_empty(inpt))
		{
			free (inpt);
			continue ;
		}
		if (!inpt || !*inpt)
		    continue ;
		add_history(inpt);
		if (find_token(inpt, &head, &gen))
		{
			reset(&gen, &head, inpt);
			printf("error token\n");
		    continue ;
		}
		if (expand_variable(&head, &gen))
		{
			reset(&gen, &head, inpt);
			printf("error expansion\n");
			continue ;
		}
		if (parse_function(&head, &gen))
		{
			reset(&gen, &head, inpt);
			printf("error function\n");
			continue ;
		}
		reset(&gen, &head, inpt);
    }
	reset(&gen, &head, inpt);
	int	i = 0;
	while (gen.envp[i] != NULL)
	{
		free (gen.envp[i]);
		i++;
	}
	free (gen.envp);
	// system("leaks minishell");
    return (0);
}
