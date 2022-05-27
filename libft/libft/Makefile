# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 09:10:41 by dmalesev          #+#    #+#              #
#    Updated: 2022/05/23 17:04:16 by dmalesev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		  ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
		  ft_strncpy.c ft_strcat.c ft_strlcat.c ft_strncat.c ft_strchr.c \
		  ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
		  ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		  ft_isprint.c ft_toupper.c ft_tolower.c ft_striteri.c \
		  ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
		  ft_striter.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
		  ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c \
		  ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
		  ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		  ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
		  ft_lstmap.c ft_lstsize.c ft_lstprint.c ft_lstappfirst.c \
		  ft_lstprelast.c ft_lstappnew.c ft_strfree.c ft_memfree.c \
		  ft_ftoa.c ft_nbrsize.c ft_atof.c

OBJECTS = $(SOURCES:.c=.o)

INCLUDES = ./

NAME = libft.a

GCC_FLAGS = -Wall -Wextra -Werror -Wconversion

CC = gcc

all: $(NAME)

$(NAME):
	@$(CC) -I $(INCLUDES) $(GCC_FLAGS) -c $(SOURCES)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo Compiled libft!

clean:
	@rm -f $(OBJECTS)

fclean:
	@rm -f $(OBJECTS) $(NAME)

re: fclean all

recln: fclean all clean
