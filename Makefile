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

OBJCD = ./src/obj/

LIB = -L libft/ -lft 

LEMIN_SRC_DIR = src/

HEADER = lem-in.h

CLEMIN =  0.1.errors.c 0.2.read_line.c 0.3.validator.c 0.4.is.c  0.6.init_structure.c \
0.7.write_coordinate.c 0.8.dashes_in_input.c 1.main.c \
2.1_parse_ants.c 2.parse_rooms.c \
3.parse_link.c 4.bfs.c 5.find_links_direction.c 6.input_cleaning.c 7.print.c\
0.5.hash_table.c 8.create_paths.c 8.create_paths2.c 9.flow.c 9.flow2.c \
let_me_free.c let_me_free_lem.c 6.2.deadlock_cleaning.c

LEMIN_SRC = $(addprefix $(LEMIN_SRC_DIR),$(CLEMIN))

LEMIN_OBJ = $(addprefix $(OBJCD),$(LEMIN_SRC:src/%.c=%.o))


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LEMIN_OBJ) $(HEADER)
	make -C libft
	gcc $(FLAGS) $(LEMIN_OBJ) -o $(NAME) $(LIB)


$(OBJCD)%.o : $(LEMIN_SRC_DIR)%.c $(HEADER)
	gcc -c $(FLAGS) $< -o $@


clean:	
	@rm -rf $(OBJCD)
	@mkdir $(OBJCD)
	make clean -C libft/

fclean: clean	
	make fclean -C libft/
	@rm -rf $(OBJCD) $(NAME)
	@mkdir $(OBJCD)

re: fclean all
