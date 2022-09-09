/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:50:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/09 10:40:01 by khatlas          ###   ########.fr       */
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

static void exe_pipe(t_matrix *matrix, int pipe_count, int *pipefds, int j)
{
    pid_t   pid;
    char    *buffer;
    int     i;

    buffer = NULL;
    pid = fork();
    if (pid == 0) //child
    {
        if (matrix->next) //check if this is not the last node, if it isn't then redirect the stdout
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
        while (i < 2 * pipe_count) //close all fds in current child since we've already made our redirections
        {
            close(pipefds[i]);
            i++;
        }
        buffer = find_path_str(matrix->matrix[0]);
        if (!buffer)
            printf("find path didnt work!\n");
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
            matrix = matrix->next;
        exe_pipe (matrix, pipe_count, pipefds, j);
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