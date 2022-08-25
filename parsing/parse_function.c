/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 02:37:39 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/25 11:34:41 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_function(t_token **head, t_general *gen)
{
    // t_token *it;
    char    *buffer;
    char    cwd[PATH_MAX];

    buffer = NULL;
    if (!head || !*head)
        return (-1);
    int     flag = 0;
    //check the token in the list of commands (still to work in the external)
    printf("token: %d\n",token_searchlst(*head));
    //get the token in the list and look for the specific case
    if (token_searchlst(*head) == ECHO_CMD) // echo
    {
        if (!ft_strncmp((*head)->content, "-n", 2) && ft_strlen((*head)->content) == 2)
        {
            flag = 1;
            (*head) = (*head)->next;
            (*head) = (*head)->next;
        }
        gen->str = ft_echo(head);
        //consider type -nnnnn... also work
    }
    //check access if exist or not
    if (token_searchlst(*head) == CD_CMD) // cd
    {
        char    cd_buff[PATH_MAX];
    
        (*head) = (*head)->next;
        if (chdir((*head)->content) != 0) 
            perror("chdir() failed");
        else
            getcwd(cd_buff, PATH_MAX);
            printf("%s\n",cd_buff);
        // changing the cwd to /tmp
        if (chdir("..") != 0) 
            printf("%s\n",cwd);

    }
    if (token_searchlst(*head) == PWD_CMD) //pwd
    {
        getcwd(cwd, PATH_MAX);
        printf("%s\n",cwd);
    }
        // case 3: //pwd
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