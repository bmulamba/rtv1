# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmulamba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/11 11:11:35 by bmulamba          #+#    #+#              #
#    Updated: 2018/09/14 11:30:40 by bmulamba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		rtv1

SRCS=		main.c\
			raycalc.c\
			light.c\
			display.c\
			inter_obj.c\
			list.c \
			rotate.c\
			shadow.c\
			key_hook.c

OBJS=		$(SRCS:.c=.o)

LIB=		-Lminilibx_macos -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	gcc -Wall -Wextra -Werror -g $(LIB) $(SRCS) -o $(NAME)

clean:
	-rm -f $(OBJS)

fclean:	clean
	-rm -f $(NAME)

re:	fclean all

.PHONY:	clean fclean all
