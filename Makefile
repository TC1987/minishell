# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcho <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/27 23:50:23 by tcho              #+#    #+#              #
#    Updated: 2019/04/11 16:02:10 by tcho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
BASE = main \
	   helpers \
	   split_input \
	   ./builtins/ft_cd \
	   ./builtins/ft_echo \
	   ./builtins/ft_env \
	   ./builtins/ft_exit \
	   ./builtins/ft_setenv \
	   ./builtins/ft_unsetenv \
	   ./get_next_line/get_next_line \
	   ./list_vector/ft_listv_add \
	   ./list_vector/ft_listv_remove \
	   ./list_vector/ft_listv_length
SRC = $(addsuffix .c, $(BASE))
OBJ = $(addsuffix .o, $(BASE))
HEADERS = -I. -I./libft -I./b_printf -I./list_vector -I./get_next_line -I./builtins
CC = gcc -Wall -Wextra -Werror -o
CC_G = gcc -Wall -Wextra -Werror -fsanitize=address -g -o
CC_V = gcc -Wall -Wextra -Werror valgrind --leak-check=full -v ./minishell
LIBS = ./libft/libft.a ./b_printf/libftprintf.a
SANITIZE = -fsanitize=address -g

all: $(NAME)

$(NAME): $(SRC) $(LIBS)
	@echo "Generating Executable"
	@$(CC) $(NAME) $(SRC) $(HEADERS) $(LIBS)

debug: $(LIBS)
	$(CC_G) $(NAME) $(SRC) $(HEADERS) $(LIBS)

valgrind: $(LIBS)
	@$(CC) $(NAME) $(SRC) $(HEADERS) $(LIBS) -g

fsanitize:
	@$(CC) $(NAME) $(SRC) $(HEADERS) $(LIBS) $(SANITIZE)

$(LIBS):
	@echo "Generating Libraries"
	@make -C ./libft
	@make -C ./b_printf

clean:
	@echo "Cleaning"
	@/bin/rm -f $(OBJ)
	@make clean -C ./libft
	@make clean -C ./b_printf

fclean: clean
	@echo "FCleaning"
	@/bin/rm -f $(NAME)
	@make fclean -C ./libft
	@make fclean -C ./b_printf

re: fclean all
