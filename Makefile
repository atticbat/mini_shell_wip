# -*- MakeFile -*-

VPATH	=	parsing helper
NAME	=	minishell
FUNCTS	=	minishell.c parse_token.c token_add_back.c token_add_front.c \
			token_clear.c token_delone.c token_last.c token_new.c token_size.c \
			testing.c
LIBFTNAME =	ft
OBJS	=	$(addprefix $(OBJ_PATH),$(notdir $(FUNCTS:.c=.o)))
CC		=	cc
CFLAGS	= 	-Wall -Werror -Wextra
OBJ_PATH =	./obj/
LIBFTPATH =	./libft/
IFLAGS	=	-I ./includes
RM 		=	/bin/rm -f
RMR		=	/bin/rm -rf
DEPEND	=	-MMD -MP

all: $(NAME)

bonus: $(BNAME)

$(OBJ_PATH) :
	mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: %.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(IFLAGS) $(DEPEND) -c $< -o $@

$(NAME): $(OBJ_PATH) $(OBJS)
	make -C $(LIBFTPATH)
	$(CC) -o $(NAME) $(IFLAGS) $(DEPEND) $(OBJS) -lreadline \
		-L $(LIBFTPATH) -l $(LIBFTNAME)

clean:
	make clean -C $(LIBFTPATH)
	$(RMR) $(OBJ_PATH)

fclean: clean
	make fclean -C $(LIBFTPATH)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(OBJ_PATH):%.o=%.d
