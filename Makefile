
NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

SRC 	= 

SRCDIR	= ./srcs/
SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(SRCS:.c=.o)
LIBNAME	= libft.a
INCDIR	= ./includes/

%.o:	%.c
			$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(NAME): $(LIBNAME) $(OBJS)
	$(CC) $(CFLAGS) -I$(INCDIR) -L. -lmlx -o $(NAME) $(OBJS) $(LIBNAME)

$(LIBNAME):
	@$(MAKE) -C ./libft
	@cp libft/$(LIBNAME) $(LIBNAME)


all: $(NAME)

clean:
	@$(MAKE) -C ./libft clean
	$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C ./libft fclean
	$(RM) $(LIBNAME) $(MLXNAME) $(NAME)

re: fclean all