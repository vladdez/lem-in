/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <klaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:42:26 by klaurine          #+#    #+#             */
/*   Updated: 2019/12/15 18:00:07 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	read_format(const char *f, t_p *params, va_list ap)
{
	size_t h;
	size_t l;

	h = 0;
	l = 0;
	read_flags(f, params);
	read_width_precis(f, params, ap);
	read_size(f, params, h, l);
	params->type = f[params->count];
}

void	read_flags(const char *f, t_p *params)
{
	size_t i;

	i = params->count;
	while ('#' == f[i] || '0' == f[i] || ' ' == f[i] || '+' == f[i] ||
			'-' == f[i])
	{
		if ('#' == f[i])
			params->hash = '#';
		else if (('-' == f[i] || '0' == f[i]) && (params->minus_zero != '-'))
			params->minus_zero = f[i];
		else if (('+' == f[i] || ' ' == f[i]) && (params->plus_space != '+'))
			params->plus_space = f[i];
		params->count++;
		i++;
	}
}

void	read_width_precis(const char *f, t_p *params, va_list ap)
{
	if ('0' <= f[params->count] && f[params->count] <= '9')
	{
		params->width = ft_atoi(f + params->count);
		while ('0' <= f[params->count] && f[params->count] <= '9')
			params->count++;
	}
	else if ('*' == f[params->count])
	{
		params->width = va_arg(ap, int);
		params->count++;
	}
	if ('.' == f[params->count] && f[++params->count] != '*')
	{
		params->precision = ft_atoi(f + params->count);
		while ('0' <= f[params->count] && f[params->count] <= '9')
			params->count++;
	}
	else if ('*' == f[params->count])
	{
		params->precision = va_arg(ap, int);
		params->count++;
	}
}

void	read_size(const char *f, t_p *params, size_t h, size_t l)
{
	size_t big_l;

	big_l = 0;
	while ('h' == f[params->count] || 'l' == f[params->count] ||
			'L' == f[params->count])
	{
		if ('h' == f[params->count])
			h++;
		else if ('l' == f[params->count])
			l++;
		else if ('L' == f[params->count])
			big_l++;
		params->count++;
	}
	if (big_l)
		params->size = 5;
	else if ((0 == l % 2 && l) || big_l == 2)
		params->size = 4;
	else if (l % 2 != 0 && l)
		params->size = 3;
	else if (h % 2 != 0 && h)
		params->size = 2;
	else if (0 == h % 2 && h)
		params->size = 1;
}

size_t	print_specificator(t_p *params, va_list ap, char f)
{
	if ('d' == f || 'i' == f)
		return (print_integer(params, ap));
	else if ('o' == f)
		return (print_octal(params, ap));
	else if ('u' == f)
		return (print_unsigned(params, ap));
	else if ('x' == f || 'X' == f)
		return (print_hexadecimal(params, ap));
	else if ('s' == f)
		return (print_string(params, ap));
	else if ('p' == f)
		return (print_pointer(params, ap));
	else if ('f' == f || 'e' == f || 'g' == f)
	{
		params->c_float = f;
		return (print_float(params, ap));
	}
	else if ('%' == f)
		return (print_percent(params));
	else
		return (print_char(params, ap));
}
