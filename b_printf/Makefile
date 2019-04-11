# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcho <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/12 19:51:35 by tcho              #+#    #+#              #
#    Updated: 2019/04/11 01:40:22 by tcho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC =  b_printf.c \
	   ft_is_space.c \
	   ft_itoa_printf.c \
	   ft_operation.c \
	   ft_pc.c \
	   ft_ps.c \
	   ft_uitoa.c
OBJ = $(addsuffix .o, $(basename $(SRC)))
CFLAGS = -Wextra -Werror -Wall -c

all: $(NAME)

$(NAME):
	@gcc $(CFLAGS) $(SRC) -I.
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
