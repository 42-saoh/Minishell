# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_org                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taekang <taekang@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/06 16:47:52 by taekang           #+#    #+#              #
#    Updated: 2021/09/06 16:47:54 by taekang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

SRC_DIR		= ./srcs/
OBJ_DIR		= ./objs/
LIBFT_DIR	= ./libft/
INCDIR		= ./includes/

LIBFT = libft.a

SRC 	=	main.c error.c utils.c check.c init.c \
			command_filter.c exec_cmd.c using_free.c \
			make_command_list.c make_command_list_2.c replace_env.c \
			redirect_util.c get_next_line_utils.c get_next_line.c \
			sig_handler.c set_connect_pipe.c redirect_filter.c \
			redirect_filter_2.c redirection_dup.c redirection_in_dup.c \
			redirection_out_dup.c exec_builtin.c merge_sort.c make_param.c \
			utils_2.c copy_envp.c write_env_file.c write_export_file.c\
			builtin_cd.c builtin_echo.c builtin_exit.c builtin_pwd.c\
			builtin_env.c builtin_unset.c builtin_export.c export_print.c\
			export_add_var.c export_file_merge.c datafile_to_temp.c\
			temp_to_datafile.c remove_var.c filter_asterisk.c\
			list_to_string.c free_utils.c status_macro.c special_positional_param.c\

OBJ_FILES = $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBS	= ${LIBFT} -lreadline -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
		$(CC) ${CFLAGS} -I$(INCDIR) -o ${NAME} $(OBJS) ${LIBS}

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)/${LIBFT} .

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) ${CFLAGS} -c $< -o $@ -I$(HOME)/.brew/opt/readline/include

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
	$(RM) -rf $(OBJ_DIR)

fclean:	clean
		$(RM) $(NAME)
		$(RM) ${LIBFT}

re: fclean all

.PHONY:	all clean fclean re
