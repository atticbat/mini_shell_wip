/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:50:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/09 14:54:13 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_pipes(t_matrix *matrix)
{
    int i;

    i = 0;
    while (matrix != NULL)
    {
        if (ft_strchr(OPERATOR, matrix->operator))
            i++;
        matrix = matrix->next;
    }
    return (i);
}

static void execute(char *cmd_path, char **arg)
{
    if (cmd_path)
        if(execv(cmd_path, arg) == -1)
            exit (-1);
    exit (0);
}

static int  redirect_right(t_matrix *matrix)
{
    if (matrix->next && matrix->next->operator == '>')
    {
        int fd;
        fd = open (matrix->next->next->matrix[0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
        if (fd == -1)
            return (-1);
        dup2(fd, STDOUT_FILENO);
        close (fd);
    }
    else if (matrix->next && matrix->next->operator == '+')
    {
        int fd;
        fd = open (matrix->next->next->matrix[0], O_CREAT | O_WRONLY | O_APPEND, 0777);
        if (fd == -1)
            return (-1);
        dup2(fd, STDOUT_FILENO);
        close (fd);
    }
    else
        return (-1);
    return (0);
}


static void exe_pipe(t_matrix *matrix, int pipe_count, int *pipefds, int j)
{
    pid_t   pid;
    char    *buffer;
    int     i;

    buffer = NULL;
    pid = fork();
    if (pid == 0) //child
    {
        printf("operator type: '%c'\n", matrix->operator);
        if (matrix->next && matrix->next->operator != '<') //check if this is not the last node, if it isn't then redirect the stdout
        {
            if (dup2(pipefds[j + 1], 1) == -1) //otherwise it will just print, so we won't need gnl
                printf("redirect stdout didnt work!\n");
        }
        if (j != 0) //check if this is not the first node, if it isn't then redirect the stdin
        {
            if (dup2(pipefds[j - 2], 0) == -1) //j increments by 2 at a time so the stdin is being set to previous loops stdout (i think)
                printf("redirect stdin didnt work!\n");
        }
        i = 0;

        /////
        if (matrix->next && matrix->next->operator == '<')
        {
            int fd;
            // int i = 10;
            fd = open (matrix->next->next->matrix[0], O_CREAT | O_RDONLY, 0777);
            if (fd == -1)
            {
                printf("error file not found");
                exit (-1);
            }
            if (matrix->next && matrix->next->next && matrix->next->next->next)
            {
                if (redirect_right(matrix->next->next))
                {
                    printf("shouldve dumped\n");
                    dup2(pipefds[0], STDOUT_FILENO);
                }
            }
            dup2(fd, STDIN_FILENO);
            close (fd);
        }
        redirect_right(matrix);
        // redirect_right(matrix);
            // dup2(pipefds[0], STDIN_FILENO); 
        ///////
        while (i < 2 * pipe_count) //close all fds in current child since we've already made our redirections
        {
            close(pipefds[i]);
            i++;
        }
        buffer = find_path_str(matrix->matrix[0]);
        if (!buffer)
            printf("find path didnt work!\n");
        /////wip


        // if (matrix->next && matrix->next->operator == '>')
        // {
        //     int fd;

        //     fd = open (matrix->next->next->matrix[0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
        //     dup2(fd, STDOUT_FILENO);
        //     close (fd);
        // }
        // else if (matrix->next && matrix->next->operator == '+')
        // {
        //     int fd;

        //     fd = open (matrix->next->next->matrix[0], O_CREAT | O_WRONLY | O_APPEND, 0777);
        //     dup2(fd, STDOUT_FILENO);
        //     close (fd);
        // }
        //////
        execute(buffer, matrix->matrix);
        free (buffer);
    }
}


void    exe_cmd(t_matrix *matrix, int pipe_count)
{
    int status;
    int i;
    int j;
    // pid_t   pid;
    int *pipefds;
    // char    *buffer;

    pipefds = malloc (sizeof (int) * (pipe_count * 2));
    i = 0;
    while (i < pipe_count)
    {
        if (pipe(pipefds + i * 2) < 0) //open up all the fds here
        {
            printf("piping fails\n");
            exit (-1);
        }
        i++;
    }
    j = 0;
    while (matrix)
    {
        if (matrix->operator == '|')
        {
            matrix = matrix->next;
            if (!matrix)
                break ;
        }
        if (matrix->operator == '>' || matrix->operator == '+' || matrix->operator == '<')
        {
            matrix = matrix->next;
            if (matrix)
                matrix = matrix->next;
            if (!matrix)
                break ;
        }
        // printf("matrix arg: '%s'\n", matrix->matrix[0]);
        exe_pipe (matrix, pipe_count, pipefds, j);
        if (matrix)
            matrix = matrix->next;
        j += 2;
    }
    i = 0;
    while (i < pipe_count * 2)
    {
        close (pipefds[i]);
        i++;
    }
    i = 0;
    while (i < pipe_count + 1)
    {
        wait (&status);
        i++;
    }
}