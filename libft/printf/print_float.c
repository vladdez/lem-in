/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:08:57 by kysgramo          #+#    #+#             */
/*   Updated: 2019/12/15 15:09:01 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_p		*ftoa_loop(t_p *params, char *value, int expoftwo)
{
	int		j;
	int		expoftwoabs;

	j = 0;
	if (expoftwo > 0)
		expoftwoabs = expoftwo;
	else
		expoftwoabs = expoftwo * 1;
	while (expoftwoabs > j)
	{
		value = ft_sum(value, value, 0, 1);
		j++;
	}
	if (expoftwo < 0)
	{
		value = ft_negexp(value);
		params->outneg = ft_sum(value, params->outneg, 1, 2);
	}
	else
		params->outpos = ft_sum(value, params->outpos, 0, 2);
	return (params);
}

char	*ft_ftoa(char *m, int e, t_p *params)
{
	char	*value;
	int		i;
	int		factor;
	int		v;
	int		expoftwo;

	i = 63;
	factor = -1;
	while (i > -1)
	{
		v = m[i];
		factor++;
		if (v == 1)
		{
			value = ft_strdup("1");
			expoftwo = e - factor;
			params = ftoa_loop(params, value, expoftwo);
		}
		i--;
	}
	value = format_specifier(params);
	free(m);
	return (value);
}

char	*bit_loop(unsigned char *num_mant)
{
	int				i;
	int				num;
	int				bit_mask;
	char			*str_mant;

	num = 0;
	i = 0;
	str_mant = ft_strnew(64);
	while (num < 8)
	{
		bit_mask = LAST_BIT2;
		while (bit_mask != 256)
		{
			str_mant[i] = (num_mant[num] & bit_mask ? 1 : 0);
			bit_mask <<= 1;
			i++;
		}
		num++;
	}
	return (str_mant);
}

char	*sub_pf(t_p *params, int e, unsigned long m)
{
	char	*str_mant;
	char	*out;

	if (e == 16384)
		out = except(m, params->sign);
	else
	{
		str_mant = bit_loop((unsigned char *)&m);
		out = ft_ftoa(str_mant, e, params);
	}
	return (out);
}

size_t	print_float(t_p *params, va_list ap)
{
	int				e;
	unsigned long	m;
	char			*out;

	if (params->outpos && params->outneg)
		free_float_params(params);
	if (ap == NULL)
		return (0);
	if (params->size == 5)
		f1l.line = va_arg(ap, long double);
	else
		f1l.line = (long double)va_arg(ap, double);
	params->sign = f1l.extend.sign;
	if (f1l.extend.exp != 1)
	{
		e = (f1l.extend.exp - 16383);
		m = f1l.extend.mant;
	}
	else
	{
		e = 1;
		m = 0;
	}
	out = sub_pf(params, e, m);
	return (write_string(out));
}
