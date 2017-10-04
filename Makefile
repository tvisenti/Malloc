# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/14 10:52:08 by tvisenti          #+#    #+#              #
#    Updated: 2017/10/04 17:17:07 by tvisenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ifeq ($(HOSTTYPE),)
# 	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
# endif
#
# NAME = libft_malloc_$(HOSTTYPE).so
#
# SRC_PATH = ./src
# OBJLIB_PATH = ./obj
#
# SRC_NAME = malloc.c free.c realloc.c alloc_size.c handler_block.c utils.c
# OBJLIB_NAME = $(LIB_NAME:.c=.o)
#
# SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
# OBJ = $(addprefix $(OBJLIB_PATH)/,$(OBJLIB_NAME))
#
# CC = gcc
# CFLAGS = -Wall -Werror -Wextra -g
#
# INC = -I includes
# LIB = libft/
#
# all: $(NAME)
#
# $(NAME): obj $(OBJ)
# 	@make -s -C $(LIB)
# 	@$(CC) $(CFLAGS) -shared -o $@ $(OBJ) $(INC) -L$(LIB) -lft
# 	@ln -sf $(NAME) libft_malloc.so
# 	@echo "\033[1;34mMalloc\t\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"
#
# $(OBJLIB_PATH)/%.o: $(LIB_PATH)/%.c
# 	@mkdir $(OBJLIB_PATH) 2> /dev/null || true
# 	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< -I $(LIB)
#
# obj:
# 	@mkdir -p obj/
#
# clean:
# 	@rm -rf obj
#
# fclean: clean
# 	@make clean -s -C $(LIB)
# 	@rm -rf $(NAME)
#
# re: fclean all
# 	@make re -s -C $(LIB)
#
# test: all
# 	gcc test0.c -o test0
# 	gcc test1.c -o test1
# 	gcc test2.c -o test2
# 	gcc test3.c -o test3
# 	gcc test3++.c -o test3++
# 	gcc test4.c -o test4
# 	gcc test5.c -o test5 -L. -lft_malloc
# 	gcc test6.c -o test6 -L . -lft_malloc
#
# .PHONY: fclean all clean re test

.PHONY: all clean fclean re

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

LIB_PATH = ./src
INC_PATH = ./inc
OBJLIB_PATH = ./obj

LIB_NAME =	malloc.c alloc_size.c handler_block.c \
			utils.c free.c realloc.c \

INC_NAME = malloc.h \

OBJLIB_NAME = $(LIB_NAME:.c=.o)

LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJLIB_PATH)/,$(OBJLIB_NAME))

all: $(NAME)
	@cd ./libft && $(MAKE)

$(NAME): obj $(OBJ)
	@make -s -C $(LIB)
	@$(CC) $(CFLAGS) -shared -o $@ $(OBJ) $(INC) -L$(LIB) -lft
	@ln -sf $(NAME) libft_malloc.so
	@echo "\033[1;34mMalloc\t\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"

$(OBJLIB_PATH)/%.o: $(LIB_PATH)/%.c
	@mkdir $(OBJLIB_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< -I $(LIB)

obj:
	@mkdir -p obj/

# $(OBJLIB_PATH)/%.o: $(LIB_PATH)/%.c
# 	@mkdir $(OBJLIB_PATH) 2> /dev/null || true
# 	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ)
	@echo "\033[1;34mMalloc\t\t\033[1;33mCleaning obj\t\033[0;32m-OK-\033[0m"

fclean: clean
	@rm -rf ./obj $(NAME) libft_malloc_.so libft_malloc.so
	@echo "\033[1;34mMalloc\t\t\033[1;33mCleaning lib\t\033[0;32m-OK-\033[0m"
	@cd ./libft && $(MAKE) fclean

re: fclean all

norme:
	@norminette $(LIB) $(INC)
	@echo "\033[1;34mMalloc\t\t\033[1;33mNorminette\t\033[0;32m-OK-\033[0m"
