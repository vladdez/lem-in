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

FLAGS = -Wall -Wextra -Werror -I. -I ./libft/libft -I ./libft/printf

LIB = -L libft/ -lft 

LEMIN_SRC_DIR = src/

HEADER = lem-in.h

CLEMIN = main.c errors.c is.c parsers.c read_line.c validator.c

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
