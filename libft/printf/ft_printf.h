/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <klaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:57:17 by klaurine          #+#    #+#             */
/*   Updated: 2019/12/15 17:58:22 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define LAST_BIT2 1
# include <stdarg.h>
# include "../libft/libft.h"
# include "stdio.h"

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

typedef struct			s_params
{
	char				hash;
	char				minus_zero;
	int					precision;
	char				plus_space;
	size_t				size;
	char				type;
	size_t				width;
	size_t				count;
	int					sign;
	char				c_float;
	char				*outpos;
	char				*outneg;
	char				*zero;
	char				*ten;
	char				*one;
}						t_p;

typedef struct			s_calc
{
	char				*zero;
	char				*ten;
	char				*one;
	char				*rem;
	char				*k;
	char				*out;
}						t_calc;

typedef struct			s_mult
{
	char				*zero;
	char				*preout;
	char				*out;
	char				*stra;
	char				*strb;
	char				*hereout;
	size_t				longest;
	unsigned int		carry;
	int					i;
}						t_mult;

typedef struct			s_sum
{
	unsigned int		carry;
	char				*carryc;
	char				*out;
	char				*stra;
	char				*strb;
	size_t				l;
	size_t				s;
}						t_sum;

typedef struct			s_subs
{
	int					carry;
	int					temp;
	int					rem;
	char				*stra;
	char				*strb;
	size_t				l;
	size_t				s;
	char				*out;
	char				*remc;
}						t_subs;

typedef struct			s_ft_printf
{
	unsigned long	mant;
	unsigned short	exp:15;
	unsigned char	sign:1;
}						t_extend;

union					u_double
{
	long double			line;
	t_extend			extend;
}						f1l;

int						ft_printf(const char *format, ...);
size_t					print_format(const char *f, va_list ap);
t_p						*create_list(void);
size_t					write_string(char *f);
int						write_char(char c);
void					read_format(const char *f, t_p *params, va_list ap);
void					read_flags(const char *f, t_p *params);
void					read_width_precis(const char *f, t_p *params,
		va_list ap);
void					read_size(const char *f, t_p *params, size_t h,
		size_t l);
size_t					print_specificator(t_p *params, va_list ap, char f);
int						ft_intlen_base(unsigned long long n, int base);
char					*ft_itoa_base(unsigned long long value, int base,
		int reg);
unsigned long long		return_unsigned(t_p *params, va_list ap);
long long				return_integer(t_p *params, va_list ap);
size_t					print_string(t_p *params, va_list ap);
char					*print_string2(t_p *params, char *str, size_t len);
char					*print_string3(t_p *params, char *str, size_t len);
size_t					print_unsigned(t_p *params, va_list ap);
char					*print_unsigned2(t_p *params, char *str, size_t len);
char					*print_width(t_p *params, char *str, size_t len);
char					*split_and_assemble(t_p *params, char *str, char *tmp);
size_t					print_pointer(t_p *params, va_list ap);
size_t					print_char(t_p *params, va_list ap);
size_t					print_char2(t_p *params, char c);
size_t					print_integer(t_p *params, va_list ap);
char					*print_integer2(t_p *params, char *str, int sign);
char					*print_integer3(t_p *params, char *str, size_t len);
void					clean_list(t_p *params);
char					*add_atributes_precision(char *tmp, char *str);
char					*plus_space(t_p *params, char *new);
char					*add_atributes_width(t_p *params, char *str, char *tmp);
size_t					print_octal(t_p *params, va_list ap);
size_t					print_hexadecimal(t_p *params, va_list ap);
size_t					print_percent(t_p *params);
char					*return_str(t_p *params, char *tmp,
		unsigned long long a);
char					*print_pointer2(t_p *params, char *str, size_t len);
void					free_float_params(t_p *params);
int						ft_chararcmp(char *a, char *b);
char					*ft_mult(char *stra, char *strb);
char					*ft_sum(char *stra, char *strb, int sw, int kek);
char					*ft_substract(char *stra, char *strb);
char					*ft_negexp(char *val);
size_t					print_float(t_p *params, va_list ap);
char					*format_specifier(t_p *params);
char					*format_e(t_p *params);
char					*g_precision(t_p *params);
char					*except(unsigned long m, int sign);
char					*cp(char *outneg, int prec, char *one);
char					*f_precision(t_p *params, int i);
void					clean_mult(t_mult *mult);
void					clean_negexp(t_calc *calc);
void					clean_sum(t_sum *sum);
char					*sjp(char *s1, char *s2, int i, int j);
void					free_float_params(t_p *params);
char					*ft_strsubf(char *s, unsigned int start, size_t len);
int						color(const char *str);

#endif
