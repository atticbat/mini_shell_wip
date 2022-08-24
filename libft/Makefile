# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 14:12:23 by khatlas           #+#    #+#              #
#    Updated: 2022/08/21 05:05:07 by khatlas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- MakeFile -*-

NAME 	= libft.a
FUNCTS 	= ft_atoi.c ft_itoa.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_toupper.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
		ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
		ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strtrim.c ft_substr.c ft_tolower.c ft_strjoinfree.c
OBJS	= $(addprefix $(OBJ_PATH),$(FUNCTS:.c=.o))
OBJ_PATH =	./obj/
IFLAGS	= -I ../includes
CC 		= cc
CFLAGS	= -Wall -Wextra -Werror
DEPEND	= -MMD -MP

all: $(NAME)

$(OBJ_PATH) :
	mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: %.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(DEPEND) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJ_PATH) $(OBJS)
	ar -rcs $@ $(OBJS)

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
	
.PHONY: all clean fclean re

-include $(OBJS:%o:%d)