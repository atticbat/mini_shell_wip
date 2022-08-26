/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2022/08/26 20:11:43 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/26 20:14:07 by khatlas          ###   ########.fr       */
=======
/*   Created: 2022/08/21 02:37:39 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/26 20:06:57 by aparedes         ###   ########.fr       */
>>>>>>> ee1314d575f446deede9567f8949787baa03439c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  parse_nl_flag(char *content)
{
    int i;

    i = 1;
    if (!content || !*(content + 1))
        return (-1);
    while (content[i] != '\0')
    {
        if (content[i] == ' ' && content[i + 1] == '\0')
            return (0);
        else if (content[i] != 'n')
            return (-1);
        i++;
    }
    return (0);
}

int parse_function(t_token **head, t_general *gen, char **envp)
{
    t_token *it;
    char    *buffer;
    char    cwd[PATH_MAX];

    buffer = NULL;
    if (!head || !*head)
        return (-1);
    int     flag = 0;
    it = *head;
    //check the token in the list of commands (still to work in the external)
    // printf("check_format: %d\n",check_format(it));
    /* APARENTLY IS DONE */
    /* check format for execution */
    if (!check_format(it))
    {
		gen->error_no = -1;
		return (gen->error_no);	
	}
    //get the token in the list and look for the specific case
    if (cmd_searchlst(it) == ECHO_CMD) // echo
    {
        it = it->next;
        if (!ft_strncmp(it->content, "-n", 2) && !parse_nl_flag(it->content))
        {
            flag = 1;
            it = it->next;
        }
        gen->str = ft_echo(&it);
    }
    if (cmd_searchlst(it) == CD_CMD) // cd
    {
        it = it->next;
        if (it->content[ft_strlen(it->content) - 1] == ' ')
            it->content[ft_strlen(it->content) - 1] = '\0';
        if (chdir(it->content) != 0) 
            perror("chdir() failed");
    }
    if (cmd_searchlst(it) == PWD_CMD) //pwd
    {
        getcwd(cwd, PATH_MAX);
        printf("%s\n",cwd);
    }
    if (cmd_searchlst(it) == ENV_CMD)
    {
        gen->str = ft_env(envp);
    }
        // case 4: //export
        // case 5: //unset
        // case 6: //env
        // case 7: //exit
    // //temporary output
    if (gen->str)
    {
        printf("%s", gen->str);
        if (flag)
            printf("%%\n");
        else
            printf("\n");
    }
    //
    return (0);
}