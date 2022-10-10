# -*- MakeFile -*-

CUSTOM	=	./custom_functions
VPATH	=	parsing helper includes list_token variable_expansion gnl \
			$(CUSTOM)/echo $(CUSTOM)/cd $(CUSTOM)/export $(CUSTOM)/unset \
			$(CUSTOM)/pwd $(CUSTOM)/env utility list_env signals \
			error_handling find_path list_matrix execution pipe
NAME	=	minishell
FUNCTS	=	minishell.c					\
				find_token.c			\
				token_add_back.c		\
				token_add_front.c		\
				token_clear.c			\
				token_delone.c			\
				token_last.c			\
				token_new.c				\
				token_size.c			\
				cmd_searchlst.c			\
				expand_variable.c		\
				expand_var_utils.c		\
				expand_var_utils2.c		\
				merge_nodes.c			\
				utilities.c				\
				string_operations.c		\
				format_checks.c			\
				string_checks.c			\
				parse_function.c		\
				ft_echo.c				\
				ft_pwd.c				\
				ft_env.c				\
				copy_envp.c				\
				ft_getenv.c				\
				ft_export.c				\
				export_utils.c			\
				export_print_vars.c		\
				ft_unset.c				\
				ft_cd.c					\
				get_next_line_utils.c 	\
				get_next_line.c 		\
				extract_quote_node.c	\
				extract_var_node.c		\
				extract_arg_node.c		\
				extract_token_node.c	\
				env_add_back.c			\
				env_add_front.c			\
				env_clear.c				\
				env_delone.c			\
				env_last.c				\
				env_new.c				\
				env_size.c				\
				matrix_add_back.c		\
				matrix_add_front.c		\
				matrix_clear.c			\
				matrix_delone.c			\
				matrix_last.c			\
				matrix_new.c			\
				matrix_size.c			\
				create_matrix.c			\
				extract_matrix.c		\
				extract_matrix_utils.c	\
				signal_handlers.c		\
				handle_error.c			\
				find_path.c				\
				check_valid_path.c		\
				execute.c				\
				builtin_executions.c	\
				pipe_utils.c			\
				pipe_utils2.c			\
				redirections.c			\
				heredoc.c				\
				testing.c
LIBFTNAME =	ft
OBJS	=	$(addprefix $(OBJ_PATH),$(notdir $(FUNCTS:.c=.o)))
CC		=	cc
CFLAGS	= 	-Wall -Werror -Wextra
OBJ_PATH =	./obj/
LIBFTPATH =	./libft/
RLPATH	=	./readline/
IFLAGS	=	-I ./includes -I ./readline
RM 		=	/bin/rm -f
RMR		=	/bin/rm -rf
DEPEND	=	-MMD -MP

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJS)
	make -C $(LIBFTPATH)
	@if [ -e "./readline/config.log" ]; then\
	    echo "config log exists";\
	else\
	    cd $(RLPATH) && sh ./configure;\
	fi
	make -C $(RLPATH)
	$(CC) -o $(NAME) $(IFLAGS) $(DEPEND) $(OBJS) -L $(LIBFTPATH) -l $(LIBFTNAME) -ltermcap \
		-L $(RLPATH) -lreadline -L $(RLPATH) -lhistory -L $(RLPATH)

$(OBJ_PATH) :
	mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: %.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(IFLAGS) $(DEPEND) -c $< -o $@

clean:
	make clean -C $(LIBFTPATH)
	make mostlyclean -C $(RLPATH)
	@if [ -e "./readline/config.log" ]; then\
		cd $(RLPATH) && rm config.log;\
	fi
	$(RMR) $(OBJ_PATH)

fclean: clean
	make fclean -C $(LIBFTPATH)
	make clean -C $(RLPATH)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
-include $(OBJS:.o=.d)
