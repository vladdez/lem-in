/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:42:26 by klaurine          #+#    #+#             */
/*   Updated: 2019/11/27 15:19:41 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_octal(t_p *params, va_list ap)
{
	unsigned long long int	a;
	char					*tmp;
	char					*str;
	size_t					len;

	a = return_unsigned(params, ap);
	tmp = ft_itoa_base(a, 8, 0);
	if (params->hash != '#' && 0 == params->precision && 0 == a)
		str = ft_strdup("");
	else if ('#' == params->hash && tmp[0] != '0')
	{
		str = ft_strjoin("0", tmp);
		ft_strdel(&tmp);
	}
	else
		str = tmp;
	len = ft_strlen(str);
	str = print_integer3(params, str, len);
	len = ft_strlen(str);
	str = print_width(params, str, len);
	return (write_string(str));
}

size_t	print_hexadecimal(t_p *params, va_list ap)
{
	unsigned long long int	a;
	char					*tmp;
	char					*str;
	size_t					len;

	a = return_unsigned(params, ap);
	if ('X' == params->type)
		tmp = ft_itoa_base(a, 16, 1);
	else
		tmp = ft_itoa_base(a, 16, 0);
	str = return_str(params, tmp, a);
	ft_strdel(&tmp);
	if ('x' == str[1] || 'X' == str[1])
		len = ft_strlen(str) - 2;
	else
		len = ft_strlen(str);
	str = print_integer3(params, str, len);
	len = ft_strlen(str);
	str = print_width(params, str, len);
	return (write_string(str));
}

char	*return_str(t_p *params, char *tmp, unsigned long long a)
{
	char *str;

	if (0 == params->precision && 0 == a)
		str = ft_strdup("");
	else if ('#' == params->hash && tmp[0] != '0')
	{
		if ('x' == params->type)
			str = ft_strjoin("0x", tmp);
		else
			str = ft_strjoin("0X", tmp);
	}
	else
		str = ft_strdup(tmp);
	return (str);
}

size_t	print_percent(t_p *params)
{
	char	*tmp;
	char	*new;
	int		i;

	i = 0;
	if (params->width > 1)
	{
		tmp = ft_strnew(params->width - 1);
		while (i < (int)(params->width - 1))
		{
			if (params->minus_zero != '0')
				tmp[i] = ' ';
			else
				tmp[i] = '0';
			i++;
		}
		if ('-' == params->minus_zero)
			new = ft_strjoin("%", tmp);
		else
			new = ft_strjoin(tmp, "%");
		ft_strdel(&tmp);
		return (write_string(new));
	}
	return (write_char('%'));
}
