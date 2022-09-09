/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:14:01 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/08 15:51:19 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef	GET_NEXT_LINE_H
// # define GET_NEXT_LINE_H
// # define BUFFER_SIZE 1024

// #include <unistd.h>
// #include <stdlib.h>

// char	*gnl_strjoin(char *s1, char *s2);
// char	*gnl_strchr(char *s, int c);
// char	*gnl_strdup(char *s1);
// size_t	gnl_strlen (char *str);
// char	*get_next_line(int fd);

// #endif


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 1

typedef struct s_static
{
	char	*store;
	char	buff[BUFFER_SIZE + 1];
}			t_static;

char	*get_next_line(int fd);
char	*gnl_strdup(const char *str);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_substr(char const *s, unsigned int start, size_t len);

#endif
