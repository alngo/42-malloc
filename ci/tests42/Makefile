# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alngo <alngo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 14:57:02 by alngo             #+#    #+#              #
#    Updated: 2020/02/11 15:10:08 by alngo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LFT := libft_malloc.so

NAME := tests42

CC := gcc
CFLAGS :=

SRC_PATH := srcs
INC_PATH := incs
OUT_PATH := out
SRC_NAME := test0.c \
			test1.c \
			test2.c \
			test3.c \
			test3bis.c \
			test4.c \
			test5.c

OUT_NAME := $(SRC_NAME:.c=)

SRC := $(addprefix $(OUT_PATH)/,$(OUT_NAME))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OUT_PATH) $(SRC)

test: $(NAME)
	./run_tests.sh

$(OUT_PATH):
	@mkdir $(OUT_PATH) 2> /dev/null || true

$(OUT_PATH)/%: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -I ../../$(INC_PATH) ../../$(LFT) $< -o $@

clean:
	$(RM) -r $(OUT_PATH)

fclean: clean

re: fclean all
