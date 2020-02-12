# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alngo <alngo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 14:57:02 by alngo             #+#    #+#              #
#    Updated: 2020/01/28 13:17:54 by alngo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OUT_PATH := outs

.PHONY: all clean fclean re test ci

all: $(NAME)
	./run_tests.sh

clean:
	$(RM) -r $(OUT_PATH)

fclean:	clean

re:	fclean all

-include $(OBJ:.o=.d)
