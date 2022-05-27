# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmalesev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 11:53:08 by dmalesev          #+#    #+#              #
#    Updated: 2022/05/27 13:29:25 by dmalesev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		gcc
FLAGS =		-Wall -Wextra -Werror
NAME =		minisynth
SRCS =		./srcs/*.c
INCL =		./includes
LIBFT =		libft/libft.a
MINXLIB_LIN =	-O -lmlx_Linux -lXext -lX11 -lm
MINXLIB =	-lmlx -framework AppKit -framework OpenGL 

all: $(NAME)

$(NAME):
	@make -C libft/ recln
	@$(CC) -o $(NAME) $(FLAGS) -I$(INCL) $(SRCS) $(LIBFT) $(MINXLIB)
	@echo "Compiled $(NAME)!"

linux:
	@make -C libft/ recln
	@$(CC) -o $(NAME) $(FLAGS) -I$(INCL) $(SRCS) $(MINXLIB_LIN) $(LIBFT)
	@echo "Compiled RTv1 (Linux version)!"

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
