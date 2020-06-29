/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 12:15:51 by kysgramo          #+#    #+#             */
/*   Updated: 2019/11/27 13:05:26 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*g_precision(t_p *params)
{
	int		neg;
	char	*tmp;

	neg = ft_strlen(params->outneg);
	if (neg > params->precision)
		params->outneg = cp(params->outneg, params->precision, params->one);
	if (params->outneg[params->precision - 1] == '0' && params->hash != '#')
	{
		params->precision--;
		while (params->outneg[params->precision] == '0')
			params->precision--;
		tmp = params->outneg;
		params->outneg = ft_strsub(params->outneg, 0, params->precision + 1);
		free(tmp);
	}
	if ((params->precision != 0 && neg != 0) || params->hash == '#')
		params->outneg = sjp(".", params->outneg, 0, 1);
	if (ft_strlen(params->outpos) == 0)
		params->outneg = sjp("0", params->outneg, 0, 1);
	if (params->sign == 1)
		params->outpos = sjp("-", params->outpos, 0, 1);
	params->outpos = sjp(params->outpos, params->outneg, 1, 1);
	return (params->outpos);
}

char	*e_prec2(t_p *params, char *new, char *one)
{
	int		neg;

	while (new[params->precision] == '0')
		params->precision--;
	new = ft_strsubf(new, 0, params->precision);
	if (params->c_float == 'g' && params->hash != '#')
	{
		while (new[params->precision - 1] == '0')
			params->precision--;
		new = ft_strsubf(new, 0, params->precision);
	}
	if (params->precision != 0)
		new = sjp(".", new, 0, 1);
	neg = ft_strlen(new);
	if (neg <= params->precision && params->precision != 0)
	{
		while (neg <= params->precision)
		{
			new = sjp(new, "0", 1, 0);
			neg++;
		}
	}
	params->outpos = sjp(one, new, 1, 1);
	return (params->outpos);
}

char	*e_precision(t_p *params, char *sign, char *e)
{
	int		len;
	int		onei;
	int		len2;
	char	*new;
	char	*one;

	onei = 0;
	while (params->outpos[onei] == '0')
		onei++;
	one = ft_strnew(1);
	one[0] = params->outpos[onei];
	len = ft_strlen(params->outpos);
	len2 = 0;
	new = ft_strnew(len);
	while (len2 != len)
	{
		new[len2] = params->outpos[len2 + onei + 1];
		len2++;
	}
	if (len > params->precision)
		new = cp(new, params->precision, params->one);
	params->outpos = e_prec2(params, new, one);
	params->outpos = sjp(params->outpos, sign, 1, 0);
	params->outpos = sjp(params->outpos, e, 1, 1);
	return (params->outpos);
}

char	*emin(t_p *params, int neg, char *e)
{
	char	*sign;
	char	*ee;

	sign = "e-";
	if (params->outneg[neg] == '0')
	{
		while (params->outneg[neg] == '0')
			neg++;
	}
	ee = ft_itoa(neg + 1);
	e = ft_sum(e, ee, 0, 2);
	params->outpos = params->outneg;
	params->outpos = e_precision(params, sign, e);
	return (params->outpos);
}

char	*format_e(t_p *params)
{
	int		pos;
	int		neg;
	char	*sign;
	char	*e;
	char	*ee;

	pos = ft_strlen(params->outpos) - 1;
	neg = 0;
	e = "00";
	if (pos >= 0)
	{
		sign = "e+";
		ee = ft_itoa(pos);
		e = ft_sum(e, ee, 0, 3);
		params->outpos = sjp(params->outpos, params->outneg, 1, 1);
		ee = params->outpos;
		params->outpos = e_precision(params, sign, e);
		free(ee);
	}
	else
		emin(params, neg, e);
	return (params->outpos);
}
