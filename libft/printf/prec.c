/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:48:47 by kysgramo          #+#    #+#             */
/*   Updated: 2019/11/27 12:11:42 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*format_f3(t_p *params, int i, char *tmp)
{
	if (params->plus_space == ' ' && params->sign != 1)
		params->outpos = sjp(" ", params->outpos, 0, 1);
	if (params->sign == 1)
		params->outpos = sjp("-", params->outpos, 0, 1);
	if (params->plus_space == '+' && params->sign != 1)
		params->outpos = sjp("+", params->outpos, 0, 1);
	i = ft_strlen(params->outpos);
	tmp = ft_memset(tmp, ' ', (size_t)(params->width - i));
	if (params->minus_zero == '-')
		params->outpos = sjp(params->outpos, tmp, 1, 0);
	else
		params->outpos = sjp(tmp, params->outpos, 0, 1);
	free(tmp);
	return (params->outpos);
}

char	*format_f2(t_p *params, int i)
{
	char	*tmp;

	tmp = ft_strnew(params->width - i);
	if ('0' == params->minus_zero)
	{
		tmp = ft_memset(tmp, '0', (size_t)(params->width - i));
		params->outpos = sjp(tmp, params->outpos, 0, 1);
		if (params->plus_space == ' ' && params->sign != 1)
			params->outpos = sjp(" ", params->outpos, 0, 1);
		if (params->sign == 1)
			params->outpos = sjp("-", params->outpos, 0, 1);
		if (params->plus_space == '+' && params->sign != 1)
			params->outpos = sjp("+", params->outpos, 0, 1);
		free(tmp);
	}
	else
		params->outpos = format_f3(params, i, tmp);
	return (params->outpos);
}

char	*format_f(t_p *params)
{
	int		i;

	params->outneg = f_precision(params, 1);
	if (params->precision != 0 || params->hash == '#')
		params->outneg = sjp(".", params->outneg, 0, 1);
	if (ft_strlen(params->outpos) == 0)
		params->outneg = sjp("0", params->outneg, 0, 1);
	params->outpos = sjp(params->outpos, params->outneg, 1, 1);
	i = ft_strlen(params->outpos);
	if (params->sign == 1 || params->plus_space == '+' || \
		params->plus_space == ' ')
		i = i + 1;
	if (params->width > 0 && params->width > (size_t)i)
		params->outpos = format_f2(params, i);
	else
	{
		if (params->plus_space == ' ' && params->sign != 1)
			params->outpos = sjp(" ", params->outpos, 0, 1);
		if (params->sign == 1)
			params->outpos = sjp("-", params->outpos, 0, 1);
		if (params->plus_space == '+' && params->sign != 1)
			params->outpos = sjp("+", params->outpos, 0, 1);
	}
	return (params->outpos);
}

char	*f_s_g(t_p *params, int neg, int pos)
{
	if (params->precision == -1)
		params->precision = 5;
	else if (params->precision == 0 || params->precision == 1)
		params->precision = 1;
	else
		params->precision = params->precision - 1;
	if (pos >= params->precision || (neg + 1) > 4)
		params->outpos = format_e(params);
	else
		params->outpos = g_precision(params);
	return (params->outpos);
}

char	*format_specifier(t_p *params)
{
	int		pos;
	int		neg;
	char	*p;

	pos = ft_strlen(params->outpos) - 1;
	neg = 0;
	if (params->outneg[neg] == '0')
	{
		while (params->outneg[neg] == '0')
			neg++;
	}
	if (params->c_float == 'g')
		params->outpos = f_s_g(params, neg, pos);
	else
	{
		if (params->precision == -1)
			params->precision = 6;
		if (params->c_float == 'e')
			params->outpos = format_e(params);
		else
			params->outpos = format_f(params);
	}
	p = params->outpos;
	return (p);
}
