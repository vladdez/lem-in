/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:42:26 by klaurine          #+#    #+#             */
/*   Updated: 2019/12/02 17:10:32 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		print_pointer(t_p *params, va_list ap)
{
	unsigned long long int	a;
	char					*tmp;
	char					*str;
	size_t					len;

	a = (unsigned long long int)va_arg(ap, void *);
	tmp = ft_itoa_base(a, 16, 0);
	str = ft_strjoin("0x", tmp);
	ft_strdel(&tmp);
	if (0 == params->precision && 0 == a)
	{
		tmp = str;
		str = ft_strdup("0x");
		ft_strdel(&tmp);
	}
	len = ft_strlen(str);
	str = print_pointer2(params, str, len);
	len = ft_strlen(str);
	str = print_width(params, str, len);
	return (write_string(str));
}

char		*print_pointer2(t_p *params, char *str, size_t len)
{
	char	*tmp;
	char	*new;
	int		i;

	i = 0;
	if (params->precision > (int)len)
	{
		tmp = ft_strnew(params->precision - len + 2);
		while (i < params->precision - (int)len + 2)
		{
			tmp[i] = '0';
			i++;
		}
		if (params->width <= (ft_strlen(tmp) + len))
			new = split_and_assemble(params, str, tmp);
		else
			new = ft_strjoin(tmp, str);
		ft_strdel(&tmp);
		ft_strdel(&str);
		return (new);
	}
	return (str);
}

size_t		print_char(t_p *params, va_list ap)
{
	char c;

	if ('c' == params->type)
		c = (char)va_arg(ap, int);
	else
		c = params->type;
	return (print_char2(params, c));
}

size_t		print_char2(t_p *params, char c)
{
	size_t	len;
	size_t	count;

	count = 0;
	if (params->width > 1)
	{
		len = params->width - 1;
		if ('-' == params->minus_zero)
			count = write_char(c);
		while (len > 0)
		{
			if (params->minus_zero != '0')
				count += write_char(' ');
			else
				count += write_char('0');
			len--;
		}
		if (params->minus_zero != '-')
			count += write_char(c);
	}
	else
		count += write_char(c);
	return (count);
}

size_t		write_string(char *f)
{
	size_t b;

	b = ft_strlen(f);
	write(1, f, b);
	ft_strdel(&f);
	return (b);
}
