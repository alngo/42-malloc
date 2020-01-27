# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alngo <alngo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 14:57:02 by alngo             #+#    #+#              #
#    Updated: 2020/01/27 13:40:42 by alngo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HOSTTYPE :=

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc_$(HOSTTYPE).so
SLNK := libft_malloc.so

CC := gcc
CFLAGS := -Wall -Wextra -Werror

SRC_PATH := srcs
OBJ_PATH := obj
INC_PATH := incs

SRC_NAME := 	malloc.c	\
				free.c		\
				realloc.c 	\
				show_alloc_mem.c

OBJ_NAME := $(SRC_NAME:.c=.o)

SRC := $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ := $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ)
	@echo "libft_malloc compilation..."
	@ar r $(NAME) $(OBJ)
	@ranlib $(NAME)
	@ln -s $(NAME) $(SLNK) 2> /dev/null || true
	@echo "Done"

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -I $(INC_PATH)/ -MMD -MP -c $< -o $@

clean:
	$(RM) -r $(OBJ_PATH)

fclean:	clean
	$(RM) -r $(NAME)
	$(RM) -r $(SLNK)

re:	fclean all

-include $(OBJ:.o=.d)
