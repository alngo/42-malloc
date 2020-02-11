# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alngo <alngo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 14:57:02 by alngo             #+#    #+#              #
#    Updated: 2020/02/11 18:04:16 by alngo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LFT := libft_malloc.so

NAME := units.out

CC := gcc
CFLAGS := 

42_TEST_PATH := 42
SRC_PATH := srcs
OBJ_PATH := objs
INC_PATH := incs
SRC_NAME := main.c \
			malloc.test.c \
			free.test.c \
			realloc.test.c \
			show_alloc_mem.test.c \
			utils.test.c

OBJ_NAME := $(SRC_NAME:.c=.o)

SRC := $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ := $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

.PHONY: all clean fclean re run

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I $(INC_PATH)/ -I ../$(INC_PATH)/ \
	   ../$(LFT) -o $(NAME)

test: $(NAME)
	make test -C $(42_TEST_PATH)/
	./units.sh

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -I $(INC_PATH)/ -I ../$(INC_PATH)/ -MMD -MP -c $< -o $@

clean:
	make clean -C $(42_TEST_PATH)
	$(RM) -r $(OBJ_PATH)

fclean:	clean
	make fclean -C $(42_TEST_PATH)
	$(RM) -r $(NAME)

re:	fclean all

-include $(OBJ:.o=.d)
