/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:42:26 by klaurine          #+#    #+#             */
/*   Updated: 2019/12/02 17:08:11 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_string(t_p *params, va_list ap)
{
	char	*str;
	size_t	len;

	str = va_arg(ap, char *);
	if (!str)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str);
	len = ft_strlen(str);
	str = print_string2(params, str, len);
	len = ft_strlen(str);
	str = print_string3(params, str, len);
	return (write_string(str));
}

char	*print_string2(t_p *params, char *str, size_t len)
{
	char	*new;
	int		i;

	i = 0;
	if (params->precision != -1 && params->precision < (int)len)
	{
		new = ft_strnew(params->precision);
		while (i < params->precision)
		{
			new[i] = str[i];
			i++;
		}
		ft_strdel(&str);
		return (new);
	}
	return (str);
}

char	*print_string3(t_p *params, char *str, size_t len)
{
	char	*tmp;
	char	*new;
	int		i;

	i = 0;
	if (params->width > len)
	{
		tmp = ft_strnew(params->width - len);
		while (i < (int)(params->width - len))
		{
			if (params->minus_zero != '0')
				tmp[i] = ' ';
			else
				tmp[i] = '0';
			i++;
		}
		if ('-' == params->minus_zero)
			new = ft_strjoin(str, tmp);
		else
			new = ft_strjoin(tmp, str);
		ft_strdel(&tmp);
		ft_strdel(&str);
		return (new);
	}
	return (str);
}

int		write_char(char c)
{
	write(1, &c, 1);
	return (1);
}
