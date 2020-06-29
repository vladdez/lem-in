/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:42:26 by klaurine          #+#    #+#             */
/*   Updated: 2019/12/04 14:10:58 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_intlen_base(unsigned long long n, int base)
{
	int i;

	i = 1;
	while (n > (unsigned long long)(base - 1))
	{
		n = n / (unsigned long long)base;
		i++;
	}
	return (i);
}

char				*ft_itoa_base(unsigned long long value, int base, int reg)
{
	static char	*abc;
	char		*s;
	int			len;

	abc = ft_strnew(16);
	if (reg == 0)
		abc = ft_strcpy(abc, "0123456789abcdef");
	else
		abc = ft_strcpy(abc, "0123456789ABCDEF");
	if (value == 0)
	{
		ft_strdel(&abc);
		return (ft_strdup("0"));
	}
	len = ft_intlen_base(value, base) - 1;
	s = ft_strnew(len + 1);
	while (value > 0)
	{
		s[len] = abc[value % base];
		value = value / base;
		len--;
	}
	ft_strdel(&abc);
	return (s);
}

unsigned long long	return_unsigned(t_p *params, va_list ap)
{
	unsigned long long int a;

	if (4 == params->size)
		a = va_arg(ap, unsigned long long);
	else if (3 == params->size)
		a = (unsigned long)va_arg(ap, unsigned long long);
	else if (2 == params->size)
		a = (unsigned short)va_arg(ap, unsigned long long);
	else if (1 == params->size)
		a = (unsigned char)va_arg(ap, unsigned long long);
	else
		a = va_arg(ap, unsigned int);
	return (a);
}

long long			return_integer(t_p *params, va_list ap)
{
	long long int a;

	if (4 == params->size)
		a = va_arg(ap, long long int);
	else if (3 == params->size)
		a = (long int)va_arg(ap, long long int);
	else if (2 == params->size)
		a = (short)va_arg(ap, long long int);
	else if (1 == params->size)
		a = (signed char)va_arg(ap, long long int);
	else
		a = va_arg(ap, int);
	return (a);
}
