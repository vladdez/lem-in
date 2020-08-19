# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/17 12:08:49 by kysgramo          #+#    #+#              #
#    Updated: 2020/02/17 12:09:07 by kysgramo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = libft.a
SRC_1 = ft_words.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		 ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
		 ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
		 ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
		 ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		 ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c \
		 ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
		 ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
		 ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
		 ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c \
		 ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c \
		 ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_strrev.c \
		 ft_sort_array.c ft_swap_bits.c ft_reverse_bits.c ft_print_bits.c \
		 ft_strndup.c get_next_line.c 

SRC_2 =	print_float.c neg_exp.c sum_char.c tools.c substr.c multiplier.c prec.c \
	prec2.c read_format.c ft_printf.c conversion.c print_integer.c \
	print_octal_x.c print_unsigned.c print_pointer_char.c print_string.c free.c \
	color.c

SRCCD1 = ./libft/
SRCCD2 = ./printf/

SRC1 = $(addprefix $(SRCCD1),$(SRC_1))
SRC2 += $(addprefix $(SRCCD2),$(SRC_2))
OFILES = $(SRC_1:.c=.o)
OFILES += $(SRC_2:.c=.o)
OBJCD = ./obj_libft/
OBJ_CLEAN = $(addprefix $(OBJ_CD),$(OFILES)) 

CC = gcc

CFLAGS = -Wall -Wextra

all: $(NAME)

$(NAME):
	@mkdir $(OBJCD)
	@echo "\033[1;33mStarting compilation..."
	@gcc -Wall -Wextra -g -c $(SRC1) $(SRC2)
	@echo "\033[0;31mCreating library..."
	@ar rc $(NAME) $(OFILES)
	@echo "\033[0;31mGenerating index..."
	@ranlib $(NAME)
	@mv $(OFILES) $(OBJCD)


$(OBJCD)%.o : $(SRC_1)%.c $(HEADER)
	gcc -c $(FLAGS) $< -o $@

clean:
	@rm -rf $(OBJCD)
	@echo "Deleting:\n\033[33m $(OFILES)\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "Deleting:\n\033[33m $(NAME)\033[0m"

re : fclean all

.PHONY: all clean fclean re