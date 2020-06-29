/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:42:26 by klaurine          #+#    #+#             */
/*   Updated: 2019/12/02 17:07:11 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_unsigned(t_p *params, va_list ap)
{
	unsigned long long int	a;
	char					*tmp;
	char					*str;
	size_t					len;

	a = return_unsigned(params, ap);
	if (0 == params->precision && 0 == a)
		tmp = ft_strdup("");
	else
		tmp = ft_itoa_base(a, 10, 0);
	len = ft_strlen(tmp);
	str = print_unsigned2(params, tmp, len);
	len = ft_strlen(str);
	str = print_width(params, str, len);
	return (write_string(str));
}

char	*print_unsigned2(t_p *params, char *str, size_t len)
{
	char	*tmp;
	char	*new;
	int		i;

	i = 0;
	if (params->precision > (int)len)
	{
		tmp = ft_strnew(params->precision - len + 1);
		while (i < params->precision - (int)len)
		{
			tmp[i] = '0';
			i++;
		}
		new = ft_strjoin(tmp, str);
		ft_strdel(&tmp);
		ft_strdel(&str);
		return (new);
	}
	return (str);
}

char	*print_width(t_p *params, char *str, size_t len)
{
	char *tmp;
	char *new;

	if (params->width > len)
	{
		len = params->width - len;
		tmp = ft_strnew(len);
		if ('0' == params->minus_zero && -1 == params->precision)
			tmp = ft_memset(tmp, '0', len);
		else
			tmp = ft_memset(tmp, ' ', len);
		if ('0' == params->minus_zero && params->type != 'u')
			new = add_atributes_width(params, str, tmp);
		else if ('0' == params->minus_zero && 'p' == params->type)
			new = split_and_assemble(params, str, tmp);
		else if ('-' == params->minus_zero)
			new = ft_strjoin(str, tmp);
		else
			new = ft_strjoin(tmp, str);
		ft_strdel(&tmp);
		ft_strdel(&str);
		return (new);
	}
	return (str);
}

char	*add_atributes_width(t_p *params, char *str, char *tmp)
{
	char *new;

	if (('+' == str[0] && '0' == tmp[0]) || ' ' == str[0])
		new = add_atributes_precision(tmp, str);
	else if ('-' == str[0] && '0' == tmp[0])
		new = add_atributes_precision(tmp, str);
	else if ('x' == str[1] || 'X' == str[1])
		new = split_and_assemble(params, str, tmp);
	else
		new = ft_strjoin(tmp, str);
	return (new);
}

char	*split_and_assemble(t_p *params, char *str, char *tmp)
{
	char *new;

	if ((('x' == params->type || 'X' == params->type) && ft_strlen(tmp) > 1
				&& '0' == tmp[0]) || 'p' == params->type)
	{
		str[1] = '0';
		new = ft_strjoin(tmp, str);
		if ('x' == params->type || 'p' == params->type)
			new[1] = 'x';
		else
			new[1] = 'X';
	}
	else if (('x' == params->type || 'X' == params->type)
			&& 1 == ft_strlen(tmp) && '0' == tmp[0])
	{
		str[1] = '0';
		if ('x' == params->type)
			str[0] = 'x';
		else
			str[0] = 'X';
		new = ft_strjoin(tmp, str);
	}
	else
		new = ft_strjoin(tmp, str);
	return (new);
}
