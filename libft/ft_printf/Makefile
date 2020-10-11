NAME = ft_printf.a

FLAGS = -Wall -Wextra -Werror

LIBFT = inc/libft

DIR_S = src/

DIR_O = obj/

INCLUDES = inc/ft_printf.h

SOURCES =	print_float.c neg_exp.c sum_char.c tools.c substr.c multiplier.c prec.c \
            	prec2.c read_format.c ft_printf.c conversion.c print_integer.c \
            	print_octal_x.c print_unsigned.c print_pointer_char.c print_string.c free.c \
            	color.c

SRCS = $(addprefix $(DIR_S),$(SOURCES))

OBJS = $(addprefix $(DIR_O),$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(DIR_O)%.o: $(DIR_S)%.c $(INCLUDES)
	@mkdir -p $(DIR_O)
	@$(CC) $(FLAGS) -I $(DIR_S) -o $@ -c $<

clean:
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all