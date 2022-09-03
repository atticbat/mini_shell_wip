/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:11:43 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/03 19:31:11 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int    execute(t_general *gen, t_matrix *matrix)
{
    // char    **cmd_matrix;
    //     cmd_matrix = malloc (sizeof (char *) * 2);
    //     cmd_matrix[1] = NULL;
    //     cmd_matrix[0] = ft_strdup("");
    if (gen->cmd_path)
    {
        //our command is wc -l
        //redirect for wc to read from fileout
        if(execv(gen->cmd_path, matrix->matrix) == -1)
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
        char    **matrix;
        char    *cmd;
        int     i;
        int     len;

        gen->matrix = NULL;
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
                if (it->content[ft_strlen(it->content) - 1] == ' ')
                    it->content[ft_strlen(it->content) - 1] = '\0'; 
                if (!check_valid_path(gen, it->content))
                    cmd = ft_strdup(it->content);
                else
                    cmd = ft_strdup("N");
                if (len == 0)
                {
                    matrix = malloc (sizeof (char*) * 2);
                    matrix[0] = ft_strdup("");
                    matrix[1] = NULL;
                }
                else
                {
                    matrix = malloc (sizeof(char *) * (len + 1));
                    matrix[len] = NULL;
                    i = 0;
                    while (it && it->type == 'a')
                    {
                        if (it->content[ft_strlen(it->content) - 1] == ' ' && (ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4))
                            it->content[ft_strlen(it->content) - 1] = '\0'; 
                        matrix[i] = ft_strdup(it->content);
                        it = it->next;
                        i++;
                    }
                }
                matrix_add_back(&gen->matrix, matrix_new(cmd, matrix));
            }
            else if (it)
            {
                cmd = malloc (sizeof(char) * 2);
                cmd[0] = it->type;
                cmd[1] = '\0';
                matrix = malloc (sizeof(char *) * 2);
                matrix[0] = ft_strdup("");
                matrix[1] = NULL;
                matrix_add_back(&gen->matrix, matrix_new(cmd, matrix));
                it = it->next;
            }
            // if (it)
            //     it = it->next;
        }

        print_all_matrix(gen->matrix);
    }
    //
    t_matrix    *matrix;

    matrix = gen->matrix;
    while (matrix != NULL)
    {
        if (cmd_searchlst(matrix->cmd) == ECHO_CMD)
            ft_echo(&matrix, gen, &flag);
        else if (cmd_searchlst(matrix->cmd) == CD_CMD)
            ft_cd(&matrix);
        else if (cmd_searchlst(matrix->cmd) == PWD_CMD)
            gen->str = ft_strdup(getcwd(cwd, PATH_MAX));
        else if (cmd_searchlst(matrix->cmd) == EXPORT_CMD)
            ft_export(&matrix, gen);
        else if (cmd_searchlst(matrix->cmd) == UNSET_CMD)
            ft_unset(&matrix, gen);
        else if (cmd_searchlst(matrix->cmd) == ENV_CMD)
            gen->str = ft_env(gen->envp);
        else if (cmd_searchlst(matrix->cmd) == EXIT_CMD)
        {
            gen->error_no = 1;
            return (gen->error_no);
        }
        else if (ft_strncmp(matrix->cmd, "N", 1))
        {
            int     fileout;
            int     filein;
            pid_t   pid;
            int     p[2];
            if(find_path(gen, matrix->cmd) == -1)
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
                execute(gen, matrix);
   
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
        if (matrix)
            matrix = matrix->next;
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