# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taesan <taesan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by taekang           #+#    #+#              #
#    Updated: 2021/08/08 17:39:01 by taesan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =			ft_atoi.c\
	   			ft_bzero.c\
	   		 	ft_calloc.c\
	   		 	ft_isalnum.c\
	   		 	ft_isalpha.c\
	   		 	ft_isascii.c\
	   		 	ft_isdigit.c\
	   		 	ft_isprint.c\
	   		 	ft_itoa.c\
	   		 	ft_memccpy.c\
	   		 	ft_memchr.c\
	   		 	ft_memcmp.c\
	   		 	ft_memcpy.c\
	   		 	ft_memmove.c\
	   		 	ft_memset.c\
	   		 	ft_putchar_fd.c\
	   		 	ft_putendl_fd.c\
	   		 	ft_putnbr_fd.c\
	   		 	ft_putstr_fd.c\
	   		 	ft_split.c\
	   		 	ft_strchr.c\
	   		 	ft_strdup.c\
	   		 	ft_strjoin.c\
	   		 	ft_strlcat.c\
	   		 	ft_strlcpy.c\
	   		 	ft_strlen.c\
	   		 	ft_strmapi.c\
	   		 	ft_strncmp.c\
	   		 	ft_strnstr.c\
	   		 	ft_strrchr.c\
	   		 	ft_strtrim.c\
	   		 	ft_substr.c\
	   		 	ft_tolower.c\
	   		 	ft_toupper.c\
				ft_strcmp.c\

BONUS_SRCS = 	ft_lstadd_back.c\
				ft_lstadd_front.c\
				ft_lstclear.c\
				ft_lstdelone.c\
				ft_lstiter.c\
				ft_lstlast.c\
				ft_lstmap.c\
				ft_lstnew.c\
				ft_lstsize.c\

OBJS = $(SRCS:.c=.o)
BONUS_OBJS =$(BONUS_SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm
RMFLAGS = -rf

AR = ar
ARFLAGS = rcs

$(NAME) : $(OBJS) $(BONUS_OBJS)
		$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(BONUS_OBJS)

all: $(NAME)

clean: 	
		$(RM) $(RMFLAGS) $(OBJS) $(BONUS_OBJS)

fclean: clean
		$(RM) $(RMFLAGS) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
