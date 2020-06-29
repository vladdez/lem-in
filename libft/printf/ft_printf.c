/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:42:26 by klaurine          #+#    #+#             */
/*   Updated: 2019/11/30 15:40:04 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "stdio.h"

int		ft_printf(const char *format, ...)
{
	size_t	i;
	va_list	ap;

	if (!format)
		return (-1);
	va_start(ap, format);
	if ('%' == format[0] && '\0' == format[1])
		return (0);
	i = print_format(format, ap);
	va_end(ap);
	return (i);
}

size_t	print_format(const char *f, va_list ap)
{
	size_t	i;
	t_p		*params;

	i = 0;
	params = create_list();
	while (f[params->count])
	{
		if ('%' == f[params->count])
		{
			params->count++;
			read_format(f, params, ap);
			i += print_specificator(params, ap, f[params->count]);
			clean_list(params);
			if ('\0' == f[params->count])
				break ;
		}
		else
			i += write_char(f[params->count]);
		params->count++;
		if ('{' == f[params->count] && '%' != f[params->count + 1])
			params->count = params->count + color(&f[params->count]);
	}
	free(params);
	params = NULL;
	return (i);
}

t_p		*create_list(void)
{
	t_p *params;

	if (!(params = (t_p *)malloc(sizeof(t_p))))
		return (NULL);
	params->hash = '\0';
	params->minus_zero = '\0';
	params->precision = -1;
	params->plus_space = '\0';
	params->size = 0;
	params->type = '\0';
	params->width = 0;
	params->count = 0;
	params->sign = 0;
	params->c_float = '\0';
	params->outpos = "";
	params->outneg = "";
	params->zero = "0";
	params->ten = "10";
	params->one = "1";
	return (params);
}

void	clean_list(t_p *params)
{
	params->hash = '\0';
	params->minus_zero = '\0';
	params->precision = -1;
	params->plus_space = '\0';
	params->size = 0;
	params->type = '\0';
	params->width = 0;
	params->sign = 0;
	params->c_float = '\0';
}
