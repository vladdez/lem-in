# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/29 13:04:05 by kysgramo          #+#    #+#              #
#    Updated: 2020/06/29 13:04:08 by kysgramo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Wextra  -I. -I ./libft/libft -I ./libft/printf

LIB = -L libft/ -lft 

LEMIN_SRC_DIR = src/

HEADER = lem-in.h

CLEMIN =  0.1.errors.c 0.2.read_line.c 0.3.validator.c 0.4.is.c 1.main.c \
2.parse_ants_rooms.c 3.parse_link.c 4.bfs.c 5.find_links_direction.c  6.imput_cleaning.c 7.print.c\
0.5.hash_table.c 8.create_paths.c 9.flow.c \
let_me_free.c let_me_free_lem.c 

LEMIN_SRC = $(addprefix $(LEMIN_SRC_DIR),$(CLEMIN))

LEMIN_OBJ = $(LEMIN_SRC:%.c=%.o)


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LEMIN_OBJ) $(HEADER)
	make -C libft
	gcc $(FLAGS) $(LEMIN_OBJ) -o $(NAME) $(LIB)

$(LEMIN_SRC_DIR)%.o : $(LEMIN_SRC_DIR)%.c $(HEADER)
	gcc -c $(FLAGS) $< -o $@


clean:	
	@rm -f $(LEMIN_OBJ)

fclean: clean	
	make fclean -C libft/
	rm -fv $(LEMIN_OBJ)

re: fclean all
