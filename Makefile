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

CLEMIN =  z_errors.c z_read_line.c z_validator.c z_is.c z_hash_table.c  z_init_structure.c \
z_write_coordinate.c z_dashes_in_input.c z_delete_links.c \
a_main.c b_init.c \
c_parse_ants.c d_parse_rooms.c \
e_parse_link.c f_bfs.c h_find_links_direction.c g_deadlock_cleaning.c j_print.c i_print_hashtable.c\
k_create_paths.c l_create_paths2.c l2_create_paths3.c m_flow.c n_flow2.c \
o_if_crash.c p_if_crash2.c\
z_let_me_free.c z_let_me_free_lem.c z_let_me_free_lem2.c 

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
