/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:11:43 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/03 16:29:58 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int    execute(t_general *gen)
{
    char    **cmd_matrix;
        cmd_matrix = malloc (sizeof (char *) * 2);
        cmd_matrix[1] = NULL;
        cmd_matrix[0] = ft_strdup("");
        if (gen->cmd_path)
        {
            //our command is wc -l
            //redirect for wc to read from fileout
            if(execv(gen->cmd_path, cmd_matrix) == -1)
                return(-1);
        }
        return(0);
}

int count_args(t_token *it)
{
    int i;

    i = 0;
    while (it && it->type == 'a')
    {
        it = it->next;
        i++;
    }
    return (i);
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
    if (!check_format(it))
    {
		gen->error_no = -1;
		return (gen->error_no);	
	}
    //matrix creation here
    {
        t_matrix    *m_head;
        char    **matrix;
        char    *cmd;
        int     i;
        int     len;

        m_head = NULL;
        matrix = NULL;
        cmd = NULL;
        i = 0;
        len = 0;
        while (it != NULL)
        {
            //count args funct
            if (it->type == 'a')
            {
                len = count_args(it);
                matrix = malloc (sizeof(char *) * (len));
                matrix[len - 1] = NULL;
                if (check_valid_path(gen, it))
                    cmd = ft_strdup(it->content);
                else
                    cmd = ft_strdup("N");
                it = it->next;
                i = 0;
                while (it && it->type == 'a')
                {
                    matrix[i] = ft_strdup(it->content);
                    printf("matrix[%d]: %s\n", i, matrix[i]);
                    it = it->next;
                    printf("i: %i\n", i);
                    i++;
                }
                matrix_add_back(&m_head, matrix_new(cmd, matrix));
                printf("I get ehre\n");
            }
            else if (it)
            {
                cmd = malloc (sizeof(char) * 2);
                cmd[0] = it->type;
                cmd[1] = '\0';
                matrix_add_back(&m_head, matrix_new(cmd, NULL));
            }
            if (it)
                it = it->next;
        }
        print_all_matrix(m_head);
        return (0);
    }
    //
    while (it != NULL)
    {
        if (cmd_searchlst(it) == ECHO_CMD) // echo
            ft_echo(&it, gen, &flag);
        else if (cmd_searchlst(it) == CD_CMD) // cd
            ft_cd(&it);
        else if (cmd_searchlst(it) == PWD_CMD) //pwd
            gen->str = ft_strdup(getcwd(cwd, PATH_MAX));
        else if (cmd_searchlst(it) == EXPORT_CMD)
            ft_export(&it, gen);
        else if (cmd_searchlst(it) == UNSET_CMD)
            ft_unset(&it, gen);
        else if (cmd_searchlst(it) == ENV_CMD)
            gen->str = ft_env(gen->envp);
        else if (cmd_searchlst(it) == EXIT_CMD)
        {
            gen->error_no = 1;
            return (gen->error_no);
        }
        else if (cmd_searchlst(it) == EXTER_CMD && it->type == 'a')
        {
            int     fileout;
            int     filein;
            pid_t   pid;
            int     p[2];
            if(find_path(gen, it) == -1)
            {
                gen->error_no = -1;
                return (gen->error_no);
            }
            if (pipe(p) == -1)
            {
                gen->error_no = -1;
                return (gen->error_no);
            }
            fileout = open(PATH_FILE_1, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0777);
            filein = open(PATH_FILE_2, O_RDONLY | O_CREAT, 0777);
            if(fileout == -1)
            {
                gen->error_no = -1;
                return (gen->error_no);
            }
            pid = fork();
            if (pid == -1)
            {
                gen->error_no = -1;
                return (gen->error_no);
            }
            if (pid == 0)  //child
            {
                close(filein); // 0
                dup2(fileout, STDOUT_FILENO);
                printf("show me the money\n");
                execute( gen);
   
            }
            else    //parent
            {
                printf("show me the bill\n");
                close(fileout); //1
            }
        }
        if (gen->str)
        {
            int fileout = open (PATH_FILE_1, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0777);
            write(fileout, gen->str, ft_strlen(gen->str));
            close (fileout);
            free(gen->str);
            gen->str = NULL;
        }
        if (it)
            it = it->next;
    }
    if (gen->str)
    {
        printf("%s", gen->str);
        if (flag)
            printf("%%\n");
        else
            printf("\n");
    }
    return (0);
}