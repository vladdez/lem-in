/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:42:26 by klaurine          #+#    #+#             */
/*   Updated: 2019/12/15 14:42:39 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		print_integer(t_p *params, va_list ap)
{
	long long	a;
	char		*str;
	char		*tmp;
	int			sign;

	sign = 0;
	a = return_integer(params, ap);
	if (a < 0)
	{
		a = -a;
		sign = 1;
	}
	if (0 == params->precision && 0 == a)
		tmp = ft_strdup("");
	else
		tmp = ft_itoa_base(a, 10, 0);
	str = print_integer2(params, tmp, sign);
	return (write_string(str));
}

char		*print_integer2(t_p *params, char *str, int sign)
{
	char	*tmp;
	char	*new;
	size_t	len;

	if (1 == sign)
	{
		tmp = str;
		str = ft_strjoin("-", str);
		ft_strdel(&tmp);
	}
	len = ft_strlen(str);
	new = print_integer3(params, str, len);
	new = plus_space(params, new);
	len = ft_strlen(new);
	new = print_width(params, new, len);
	return (new);
}

char		*print_integer3(t_p *params, char *str, size_t len)
{
	int		dif;
	char	*tmp;
	char	*new;

	if (params->precision >= (int)len)
	{
		if ('-' == str[0])
			dif = params->precision - (int)len + 1;
		else
			dif = params->precision - (int)len;
		tmp = ft_strnew(dif);
		while (dif > 0)
		{
			tmp[dif - 1] = '0';
			dif--;
		}
		if (('x' == params->type || 'X' == params->type) &&
				('x' == str[1] || 'X' == str[1]))
			new = split_and_assemble(params, str, tmp);
		else
			new = add_atributes_precision(tmp, str);
		ft_strdel(&str);
		ft_strdel(&tmp);
	}
	return (params->precision >= (int)len ? new : str);
}

char		*add_atributes_precision(char *tmp, char *str)
{
	char *new;

	if ('-' == str[0] && tmp)
	{
		str[0] = tmp[0];
		tmp[0] = '-';
		new = ft_strjoin(tmp, str);
	}
	else if ('+' == str[0] && tmp)
	{
		str[0] = tmp[0];
		tmp[0] = '+';
		new = ft_strjoin(tmp, str);
	}
	else if (' ' == str[0] && tmp)
	{
		str[0] = tmp[0];
		tmp[0] = ' ';
		new = ft_strjoin(tmp, str);
	}
	else
		new = ft_strjoin(tmp, str);
	return (new);
}

char		*plus_space(t_p *params, char *new)
{
	char *str;

	if (!ft_strchr(new, '-') && params->plus_space)
	{
		if ('+' == params->plus_space)
			str = ft_strjoin("+", new);
		else
			str = ft_strjoin(" ", new);
		ft_strdel(&new);
	}
	else
		str = new;
	return (str);
}
