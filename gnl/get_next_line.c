/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:00:29 by aparedes          #+#    #+#             */
/*   Updated: 2022/09/08 15:56:29 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*gnl_new_text(char *line)
// {
// 	int		index;
// 	int		k;
// 	char	*text;

// 	index = 0;
// 	while (line[index] !='\n' && line[index])
// 		index++;
// 	if (!line[index])
// 	{
// 		free(line);
// 		return(NULL);
// 	}
// 	text = malloc(sizeof(char) * (gnl_strlen(line) - index + 1));
// 	if (!text)
// 		return(NULL);
// 	index++;
// 	k = 0;
// 	while(line[index])
// 		text[k++]= line[index++];
// 	text[k] = '\0';
// 	free(line);
// 	return (text);	
// }

// static char	*gnl_get_line(char *str)
// {
// 	char	*line;
// 	int		index;

// 	index = 0;
// 	if(str[index] == '\0')
// 		return (NULL);
// 	while (str[index] !='\n' && str[index])
// 		index++;
// 	line = malloc(sizeof(char) * (index + 2));
// 	if(!line)
// 		return(NULL);
// 	index = 0;
// 	while (str[index] != '\n' && str[index])
// 	{
// 		line[index] = str[index];
// 		index++;
// 	}
// 	if (str[index] == '\n')
// 	{
// 		line[index] = str[index];
// 		index ++;
// 	}
// 	line[index] = '\0';
// 	return (line);
// }

// char	*get_next_line(int fd)
// {
// 	int			readed;
// 	char		*buffer;
// 	char		*line;
// 	static char	*text;

// 	if (fd < 0 || BUFFER_SIZE < 1)
// 		return (NULL);
// 	readed = 1;
// 	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	while (readed != 0 && !(gnl_strchr(text, '\n')))
// 	{
// 		readed = read(fd, buffer, BUFFER_SIZE);
// 		if (readed == -1)
// 		{
// 			free(buffer);
// 			return (NULL);
// 		}
// 		buffer[readed] = '\0';
// 		text = gnl_strjoin(text, buffer);
// 	}
// 	free(buffer);
// 	line = gnl_get_line(text);
// 	text = gnl_new_text(text);
// 	return (line);
// }

static char	*store_append(char *store, char *buff, char **hold)
{
	if (store == NULL)
		store = gnl_strdup (buff);
	else
	{
		*hold = gnl_strjoin(store, buff);
		free (store);
		return (*hold);
	}
	return (store);
}

static char	*free_gnl(char *hold)
{
	if (hold)
		free (hold);
	return (NULL);
}

static char	*generate_string(char *store, char **out, char **hold, int len)
{
	if (store[len] == '\n')
	{
		*out = gnl_substr(store, 0, len + 1);
		*hold = gnl_strdup(&(store[len + 1]));
		free (store);
		return (*hold);
	}
	else
	{
		if (store[0] == '\0')
			store = NULL;
		free (*hold);
		*out = gnl_strdup(store);
		return (NULL);
	}
}

static char	*gnl_strchr(const char *str, int c)
{
	c = c % 128;
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return ((char *) str);
		str++;
	}
	if (c == 0)
		return ((char *) str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_static	ctnr;
	char			*hold;
	char			*out;
	int				len;

	hold = NULL;
	out = NULL;
	len = 1;
	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1024)
		return (NULL);
	while (len > 0 && !(gnl_strchr(ctnr.store, '\n')))
	{
		len = read (fd, ctnr.buff, BUFFER_SIZE);
		if (*(ctnr.buff) == '\0' || len == -1)
			return (free_gnl(hold));
		(ctnr.buff)[len] = '\0';
		ctnr.store = store_append(ctnr.store, ctnr.buff, &hold);
	}
	len = 0;
	while ((ctnr.store)[len] != '\n' && (ctnr.store)[len] != '\0')
		len++;
	ctnr.store = generate_string(ctnr.store, &out, &hold, len);
	return (out);
}


/* 
int   main()
{
	int fd;
	char *line;

	fd = open("text1", O_RDONLY);

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
			printf("%s", line);
			free(line);
	}
	system("leaks a.out");
} */
