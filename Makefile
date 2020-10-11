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


NAME			=	lem-in
INC_NAME		=	lem_in.h

LIB_PATH		=	libft/
LIB_INC_PATH	=	libft/
LIB_NAME		=	libft.a

SRC_PATH		=	src/
INC_PATH		=	inc/
OBJ_PATH		=	obj/

SRC_NAME		=	z_errors.c z_read_line.c z_validator.c z_is.c z_hash_table.c  z_init_structure.c \
                    z_write_coordinate.c z_dashes_in_input.c z_delete_links.c \
                    a_main.c b_init.c \
                    c_parse_ants.c d_parse_rooms.c \
                    e_parse_link.c f_bfs.c h_find_links_direction.c g_deadlock_cleaning.c j_print.c i_print_hashtable.c\
                    k_create_paths.c  \
					l_create_paths2.c  l2_create_paths3.c m_flow.c n_flow2.c \
                    o_if_crash.c p_if_crash2.c\
                    z_let_me_free.c z_let_me_free_lem.c z_let_me_free_lem2.c

SRC				=	$(addprefix $(SRC_PATH), $(SRC_NAME))
INC				=	$(addprefix $(INC_PATH), $(INC_NAME))
OBJ				=	$(addprefix $(OBJ_PATH), $(SRC_NAME:.c=.o))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -O2 -march=native
IFLAGS			=	-I $(INC_PATH). -I $(LIB_PATH).
LFLAGS			=	-L $(LIB_PATH) -lft

LIB				=	make -C $(LIB_PATH)

.PHONY:	all clean fclean re lib

$(OBJ_PATH)%.o:		$(SRC_PATH)%.c $(INC)
					@mkdir -p $(OBJ_PATH)
					$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

all:				$(NAME)

$(NAME):			$(OBJ)

					$(LIB)
					$(CC) $(CFLAGS) $(IFLAGS) -o $@ $^ $(LFLAGS)

clean:
					make clean -C $(LIB_PATH)
					rm -rf $(OBJ_PATH)

fclean:				clean
					make fclean -C $(LIB_PATH)
					rm -f $(NAME)

re:					fclean all
