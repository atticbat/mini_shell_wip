/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:11:43 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/27 23:13:18 by khatlas          ###   ########.fr       */
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

int parse_function(t_token **head, t_general *gen)
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
    else if (cmd_searchlst(it) == CD_CMD) // cd
        ft_cd(it);
    else if (cmd_searchlst(it) == PWD_CMD) //pwd
        gen->str = ft_strdup(getcwd(cwd, PATH_MAX));
    else if (cmd_searchlst(it) == EXPORT_CMD)
    {
        it = it->next;
        gen->envp = ft_export(gen->envp, it->content);
    }
    else if (cmd_searchlst(it) == ENV_CMD)
        gen->str = ft_env(gen->envp);
    // case 5: //unset
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