/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:15:13 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/06 22:42:03 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int    execute(char *cmd_path, char **arg)
{
    if (cmd_path)
    {
        if(execv(cmd_path, arg) == -1)
            return(-1);
    }
    return(0);
}

int execute_cases(t_general *gen)
{
    t_execute temp;
    t_matrix    *matrix;

    matrix = gen->matrix;
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
        int fileout;
        fileout = open(PATH_FILE_1, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0777);

        if(pid2 == 0)
        {
            dup2(fd[0], STDIN_FILENO);
            dup2(fileout, STDOUT_FILENO);
            close(fd[1]); 
            close(fd[0]); 
            close(fileout);
            execute(gen->cmd_path2, temp.arg2);
        }
        close(fd[1]); 
        close(fd[0]); 
        close(fileout); 
        waitpid(pid2, NULL, 0);
        waitpid(pid1, NULL, 0);
    }

/////////////////////////////////////////
/* print from the fileout */

    char *buffer_rst;
    int file_open;

    file_open = open(PATH_FILE_1, O_RDONLY, 0777);
    if(file_open == -1)
        return 0;
    buffer_rst = NULL;
    while(1)
    {
        buffer_rst = get_next_line(file_open);
        if(!buffer_rst)
            break;
        printf("%s",buffer_rst);
        free(buffer_rst);
    }
    close (file_open);
//////////////////////////////////////////
    return (0);
}