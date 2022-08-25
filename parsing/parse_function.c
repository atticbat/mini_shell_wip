/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:37:39 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/25 14:25:16 by khatlas          ###   ########.fr       */
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
        if (content[i] != 'n')
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
    printf("token: %d\n",cmd_searchlst(it));
    //get the token in the list and look for the specific case
    if (cmd_searchlst(it) == ECHO_CMD) // echo
    {
        it = it->next;
        it = it->next;
        if (!ft_strncmp(it->content, "-n", 2) && !parse_nl_flag(it->content))
        {
            flag = 1;
            it = it->next;
            it = it->next;
        }
        gen->str = ft_echo(&it);
        //consider type -nnnnn... also work //done 
    }
    //check access if exist or not
    if (cmd_searchlst(it) == CD_CMD) // cd
    {
        // char    cd_buff[PATH_MAX];
    
        it = it->next;
        it = it->next;
        if (chdir(it->content) != 0) 
            perror("chdir() failed");
        // else
        //     getcwd(cd_buff, PATH_MAX);
        //     printf("%s\n",cd_buff);
        // changing the cwd to /tmp
        // if (chdir("..") != 0) 
        //     printf("%s\n",cwd);

    }
    if (cmd_searchlst(it) == PWD_CMD) //pwd
    {
        getcwd(cwd, PATH_MAX);
        printf("%s\n",cwd);
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