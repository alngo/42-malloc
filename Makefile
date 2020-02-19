# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alngo <alngo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 14:57:02 by alngo             #+#    #+#              #
#    Updated: 2020/02/19 11:39:23 by alngo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HOSTTYPE :=

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc_$(HOSTTYPE).so
SLNK := libft_malloc.so

CC := gcc
CFLAGS := -Wall -Wextra -Werror -DDEBUG

SRC_PATH := srcs
OBJ_PATH := objs
INC_PATH := incs
SRC_NAME := 	malloc.c			\
				free.c				\
				realloc.c 			\
				show_alloc_mem.c 	\
				utils.c				\
				heap.c				\
				out.c				\
				block.c 			\
				fit.c

OBJ_NAME := $(SRC_NAME:.c=.o)

SRC := $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ := $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

.PHONY: all clean fclean re test ci

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ)
	@echo "libft_malloc compilation..."
	$(CC) $(CFLAGS) -shared -fPIC -o $(NAME) $(OBJ)
	@ln -sf $(NAME) $(SLNK) 2> /dev/null || true
	@echo "Done"

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -I $(INC_PATH)/ -MMD -MP -c -fPIC $< -o $@

clean:
	make clean -C ci/
	make clean -C tests/
	$(RM) -r $(OBJ_PATH)

fclean:	clean
	make fclean -C ci/
	make fclean -C tests/
	$(RM) -r $(NAME)
	$(RM) -r $(SLNK)

ci: $(NAME)
	make test -C ci/

test: $(NAME)
	make -C tests/

re:	fclean all

-include $(OBJ:.o=.d)
