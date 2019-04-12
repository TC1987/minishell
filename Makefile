# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcho <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/27 23:50:23 by tcho              #+#    #+#              #
#    Updated: 2019/04/11 20:11:07 by tcho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
BASE = ./builtins/ft_cd \
	   ./builtins/ft_echo \
	   ./builtins/ft_env \
	   ./builtins/ft_exit \
	   ./builtins/ft_setenv \
	   ./builtins/ft_unsetenv \
	   ./get_next_line/get_next_line \
	   ./list_vector/ft_listv_add \
	   ./list_vector/ft_listv_remove \
	   ./list_vector/ft_listv_length \
	   ./src/get \
	   ./src/input \
	   ./src/sanitize_input \
	   ./src/display \
	   ./src/free_and_str \
	   ./src/exec_do \
	   ./src/split_input \
	   ./src/main
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
	@echo "creating executable"
	@$(CC) $(NAME) $(SRC) $(HEADERS) $(LIBS)

debug: $(LIBS)
	$(CC_G) $(NAME) $(SRC) $(HEADERS) $(LIBS)

valgrind: $(LIBS)
	@$(CC) $(NAME) $(SRC) $(HEADERS) $(LIBS) -g

fsanitize:
	@$(CC) $(NAME) $(SRC) $(HEADERS) $(LIBS) $(SANITIZE)

$(LIBS):
	@make -C ./libft
	@echo "creating libft"
	@make -C ./b_printf
	@echo "creating b_printf"

clean:
	@echo "cleaning files"
	@/bin/rm -f $(OBJ)
	@make clean -C ./libft
	@make clean -C ./b_printf

fclean: clean
	@echo "fcleaning files"
	@/bin/rm -f $(NAME)
	@make fclean -C ./libft
	@make fclean -C ./b_printf

re: fclean all
