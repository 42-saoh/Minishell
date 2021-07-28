NAME	= minishell

CC		= gcc #arch -x86_64
#CFLAGS	= -Wall -Wextra -Werror

SRCDIR		= ./srcs/
LIBFT_DIR	= ./libft/
INCDIR		= ./includes/

LIBFT = libft.a

SRC 	=	main.c data_set.c error.c utils.c \
			check.c readline.c init.c input_filter.c
		 

SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(SRCS:.c=.o)

LIBS	= -lreadline

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
		$(CC) ${CFLAGS} -I$(INCDIR) -o ${NAME} $(OBJS) ${LIBFT} ${LIBS}

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)/${LIBFT} .

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)
		$(RM) ${LIBFT}

re: fclean all

.PHONY:	all bonus clean fclean re