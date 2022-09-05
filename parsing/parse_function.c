/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:11:43 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/05 16:54:09 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int    execute(char *cmd_path, char **arg)
{
    // char    **cmd_matrix;
    //     cmd_matrix = malloc (sizeof (char *) * 2);
    //     cmd_matrix[1] = NULL;
    //     cmd_matrix[0] = ft_strdup("");
    if (cmd_path)
    {
        //our command is wc -l
        //redirect for wc to read from fileout
        if(execv(cmd_path, arg) == -1)
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
    // char    cwd[PATH_MAX];

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
        char    operator;
        int     i;
        int     len;

        gen->matrix = NULL;
        matrix = NULL;
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
                    operator = 'F';
                else
                    operator = 'N';
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
                        if (it->content[ft_strlen(it->content) - 1] == ' ' && (ft_strncmp(matrix[0], "echo", 4) && ft_strlen(matrix[0]) == 4))
                            it->content[ft_strlen(it->content) - 1] = '\0'; 
                        matrix[i] = ft_strdup(it->content);
                        it = it->next;
                        i++;
                    }
                }
                matrix_add_back(&gen->matrix, matrix_new(operator, matrix));
            }
            else if (it)
            {
                operator = it->type;
                matrix = malloc (sizeof(char *) * 2);
                matrix[0] = ft_strdup("");
                matrix[1] = NULL;
                matrix_add_back(&gen->matrix, matrix_new(operator, matrix));
                it = it->next;
            }
        }

        // print_all_matrix(gen->matrix);
    }
    //
    t_matrix    *matrix;
    matrix = gen->matrix;


    /* select the type of arg */
    // t_matrix    *arg1;
    // t_matrix    *arg2;
    // int i =0;
    t_execute temp;
    ft_bzero(&temp, sizeof(t_execute));
    if(matrix)
    {
        temp.arg1 = matrix->matrix;
        matrix = matrix->next;
        if(matrix)
        {
            temp.operator = matrix->operator;
            matrix = matrix->next;
            if(matrix)
                temp.arg2 = matrix->matrix;
        }
    }
    print_execute(temp);
    //we need to separate this, till now arg1 only used
    // if (cmd_searchlst(temp.arg1[0]) == ECHO_CMD)
    //     ft_echo(temp, gen, &flag);
    // else if (cmd_searchlst(temp.arg1[0]) == CD_CMD)
    //     ft_cd(temp.arg1);
    // else if (cmd_searchlst(temp.arg1[0]) == PWD_CMD)
    //     gen->str = ft_strdup(getcwd(cwd, PATH_MAX));
    // else if (cmd_searchlst(temp.arg1[0]) == EXPORT_CMD)
    //     ft_export(temp.arg1, gen);
    // else if (cmd_searchlst(temp.arg1[0]) == UNSET_CMD)
    //     ft_unset(temp.arg1, gen);
    // else if (cmd_searchlst(temp.arg1[0]) == ENV_CMD)
    //     gen->str = ft_env(gen->envp);
    // else if (cmd_searchlst(temp.arg1[0]) == EXIT_CMD)
    // {
    //     gen->error_no = 1;
    //     return (gen->error_no);
    // }
    ///////repeat arg2
    // if (temp.operator == '|' && temp.arg1 && temp.arg2)
    if(temp.arg1)
    {

        /*  checkerfor our CMD 
        check list

        check 
        if(arg1 &&arg2)
            if(cmd_searchlst(temp.arg2[0]) == "commands" )
                execute our cmd
        */
        




        if(find_path(gen, temp) == -1)
        {
            gen->error_no = -1;
            return (gen->error_no);
        }
        int fd[2];
        if(pipe(fd) == -1)
        {
            gen->error_no = -1;
            return (gen->error_no);
        }

        int pid1;
        pid1 = fork();

        if(pid1 == 0)
        {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]); 
            close(fd[1]); 
            execute(gen->cmd_path1, temp.arg1);
        }
        int pid2;
        pid2 = fork();
        int fileout = open(PATH_FILE_1, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0777);
        if(pid2 == 0)
        {
            dup2(fd[0], STDIN_FILENO);
            dup2(fileout, STDOUT_FILENO);
            close(fd[1]); 
            close(fd[0]); 
            close(fileout);
            if()
            execute(gen->cmd_path2, temp.arg2);
        }
        close(fd[1]); 
        close(fd[0]); 
        close(fileout); 
        waitpid(pid2, NULL, 0);
        waitpid(pid1, NULL, 0);
    }
/////////////////////////////////////////


    if (gen->str)
    {
        int fileout = open (PATH_FILE_1, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0777);
        write(fileout, gen->str, ft_strlen(gen->str));
        close (fileout);
        free(gen->str);
        gen->str = NULL;
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