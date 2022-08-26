# -*- MakeFile -*-

VPATH	=	parsing helper includes list_token variable_expansion echo utility pwd env
NAME	=	minishell
FUNCTS	=	minishell.c				\
				find_token.c		\
				token_add_back.c	\
				token_add_front.c	\
				token_clear.c		\
				token_delone.c		\
				token_last.c		\
				token_new.c			\
				token_size.c		\
				token_searchlst.c	\
				expand_variable.c	\
				utilities.c			\
				parse_function.c	\
				ft_echo.c			\
				ft_pwd.c			\
				ft_env.c			\
				copy_envp.c			\
				ft_getenv.c			\
				testing.c
LIBFTNAME =	ft
OBJS	=	$(addprefix $(OBJ_PATH),$(notdir $(FUNCTS:.c=.o)))
CC		=	cc
CFLAGS	= 	-Wall -Werror -Wextra
OBJ_PATH =	./obj/
LIBFTPATH =	./libft/
BREW	=	$(shell brew --prefix)
IFLAGS	=	-I ./includes -I $(BREW)/Cellar/readline/include
RM 		=	/bin/rm -f
RMR		=	/bin/rm -rf
DEPEND	=	-MMD -MP

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJS)
	make -C $(LIBFTPATH)
	$(CC) -o $(NAME) $(IFLAGS) $(DEPEND) $(OBJS) -lreadline \
		-L $(LIBFTPATH) -l $(LIBFTNAME) -L $(BREW)/Cellar/readline/8.1.2/lib -lreadline

$(OBJ_PATH) :
	mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: %.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(IFLAGS) $(DEPEND) -c $< -o $@

clean:
	make clean -C $(LIBFTPATH)
	$(RMR) $(OBJ_PATH)

fclean: clean
	make fclean -C $(LIBFTPATH)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
-include $(OBJS:.o=.d)
