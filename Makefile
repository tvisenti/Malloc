# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/14 10:52:08 by tvisenti          #+#    #+#              #
#    Updated: 2017/10/09 17:05:34 by tvisenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC_PATH = ./src
SRC_NAME =	malloc.c free.c realloc.c alloc_size.c handler_block.c \
			utils.c display.c bonus.c

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ = $(SRC:.c=.o)
INC = -I includes
LIB_INC = -I libft/includes
LIB = libft/
MAL = inc/malloc.h

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB)
	@$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJ) -lft -L $(LIB) $(INC) $(LIB_INC)
	@ln -sf $(NAME) $(LINK)
	@echo "\033[1;34mMalloc\t\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"

%.o: %.c
	@$(CC) -c $(CFLAGS) $(INC) $(LIB_INC) $^ -o $@ -fPIC

clean:
	@rm -rf $(OBJ)

fclean: clean
	@cd ./libft/ && $(MAKE) fclean
	@rm -rf $(NAME)
	@rm -rf $(LINK)

re: fclean all

norme:
	@cd libft && make norme
	@echo "\033[1;34mMalloc\t\t\033[1;33mNorminette\t\033[0;32m-OK-\033[0m"
	@norminette $(SRC) $(MAL)

.PHONY: fclean all clean re norme
