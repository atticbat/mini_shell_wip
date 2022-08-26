/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:23:10 by khatlas           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/26 20:12:38 by khatlas          ###   ########.fr       */
=======
/*   Updated: 2022/08/26 20:04:49 by aparedes         ###   ########.fr       */
>>>>>>> ee1314d575f446deede9567f8949787baa03439c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void interrupt_handler(int signum)
{
    (void) signum;
    write (1, "\n", 1);
    rl_free_line_state();
    rl_on_new_line();
    write (1, PROMPT, ft_strlen(PROMPT));
    rl_redisplay();
}

int main (int argc, char **argv, char **envp)
{
	t_token		*head;
    char		*inpt;
	t_general	gen; // no using

	(void) argc;
	(void) argv;
	envp = copy_envp(envp);
	// (void) envp;
	head = NULL;
	inpt = NULL;
	reset(&gen, &head, inpt);
    signal(SIGINT, interrupt_handler);
    while (1)
    {
		inpt = readline(PROMPT);
		if (!inpt || !*inpt)
		    continue ;
		add_history(inpt);
		if (find_token(inpt, &head, &gen))
		{
			reset(&gen, &head, inpt);
			//put error glossary here
			printf("error xd\n");
		    continue ;
		}
		if (expand_variable(&head, &gen, envp))
		{
			reset(&gen, &head, inpt);
			//put error glossary here
			printf("error xd\n");
			continue ;
		}
		if (parse_function(&head, &gen, envp))//sending *head and *gen
		{
			reset(&gen, &head, inpt);
			//put error glossary here
			printf("error xd\n");
			continue ;
		}
<<<<<<< HEAD
=======
		if (parse_function(&head, &gen))//sending *head and *gen
		{
			reset(&gen, &head, inpt);
			//put error glossary here
			printf("error xd\n");
			continue ;
		}
>>>>>>> ee1314d575f446deede9567f8949787baa03439c
		reset(&gen, &head, inpt);
		// system("leaks minishell");
		// exit (0);
    }
    return (0);
}
