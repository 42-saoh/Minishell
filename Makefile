NAME	= minishell

CC		= gcc -g #-fsanitize=address #arch -x86_64
#CFLAGS	= -Wall -Wextra -Werror

SRC_DIR		= ./srcs/
OBJ_DIR		= ./objs/
LIBFT_DIR	= ./libft/
INCDIR		= ./includes/

LIBFT = libft.a

SRC 	=	main.c error.c utils.c check.c readline.c init.c \
			command_filter.c redirect_filter.c exec_cmd.c using_free.c \
			make_command_list.c replace_env.c \

SRCS	= $(addprefix $(SRC_DIR), $(SRC))

OBJ_FILES = $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBS	= -lreadline

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
		$(CC) ${CFLAGS} -I$(INCDIR) -o ${NAME} $(OBJS) ${LIBFT} ${LIBS}

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)/${LIBFT} .

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) ${CFLAGS} -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
	$(RM) -rf $(OBJ_DIR)

fclean:	clean
		$(RM) $(NAME)
		$(RM) ${LIBFT}

re: fclean all

.PHONY:	all bonus clean fclean re