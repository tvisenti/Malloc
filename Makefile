# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/14 10:52:08 by tvisenti          #+#    #+#              #
#    Updated: 2017/10/02 15:38:32 by tvisenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = malloc.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIB_PATH = ./src
OBJLIB_PATH = ./obj

LIB_NAME =	malloc.c alloc_size.c handler_block.c init_block.c free.c \

OBJLIB_NAME = $(LIB_NAME:.c=.o)

LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
OBJLIB = $(addprefix $(OBJLIB_PATH)/,$(OBJLIB_NAME))

all: $(NAME)
	@cd ./libft && $(MAKE)

$(NAME): $(OBJLIB)
	@ar rc	$(NAME) $(OBJLIB)
	@ranlib	$(NAME)
	@echo "\033[1;34mMalloc\t\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"

$(OBJLIB_PATH)/%.o: $(LIB_PATH)/%.c
	@mkdir $(OBJLIB_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJLIB)
	@echo "\033[1;34mMalloc\t\t\033[1;33mCleaning obj\t\033[0;32m-OK-\033[0m"

fclean: clean
	@rm -rf ./obj $(NAME)
	@echo "\033[1;34mMalloc\t\t\033[1;33mCleaning lib\t\033[0;32m-OK-\033[0m"
	@cd ./libft && $(MAKE) fclean

re: fclean all

norme:
	@norminette $(LIB) $(INC)
	@echo "\033[1;34mMalloc\t\t\033[1;33mNorminette\t\033[0;32m-OK-\033[0m"
