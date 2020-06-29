/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neg_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 12:25:48 by kysgramo          #+#    #+#             */
/*   Updated: 2019/11/23 12:25:52 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_calc	*create_calc(void)
{
	t_calc *calc;

	if (!(calc = (t_calc *)malloc(sizeof(t_calc))))
		return (NULL);
	calc->zero = "0";
	calc->ten = "10";
	calc->one = "1";
	calc->rem = ft_strdup("10");
	calc->out = ft_strdup("");
	return (calc);
}

char	*ft_rem(char *val, t_calc *calc)
{
	char	*xl;
	char	*k;
	char	*temp;
	int		i;

	i = 2;
	k = ft_strdup("1");
	xl = ft_strdup("1");
	while (ft_chararcmp(calc->rem, xl) >= 0 && i < 10)
	{
		k = ft_sum(k, ft_strdup("1"), 0, 2);
		temp = xl;
		xl = ft_mult(val, k);
		free(temp);
		i++;
	}
	if (i != 10 || (i == 10 && ft_chararcmp(calc->rem, xl) <= 0))
		k = ft_substract(k, calc->one);
	free(xl);
	return (k);
}

char	*negexp_loop(int q, size_t len, t_calc *calc, char *val)
{
	int		w;
	char	*temp;

	w = 0;
	if (q == 0)
	{
		while (len != 0)
		{
			calc->out = sjp(calc->out, calc->zero, 1, 0);
			temp = calc->rem;
			calc->rem = ft_mult(calc->rem, calc->ten);
			free(temp);
			len--;
		}
	}
	while (ft_chararcmp(calc->rem, val) <= 0)
	{
		w++;
		temp = calc->rem;
		calc->rem = ft_mult(calc->rem, calc->ten);
		free(temp);
		if (w > 1)
			calc->out = sjp(calc->out, calc->zero, 1, 0);
	}
	return (calc->out);
}

char	*ft_negexp(char *val)
{
	t_calc		*calc;
	char		*k;
	int			q;
	size_t		len;
	char		*temp;

	calc = create_calc();
	q = 0;
	len = ft_strlen(val) - 1;
	while (ft_chararcmp(calc->rem, calc->zero) != 0)
	{
		calc->out = negexp_loop(q, len, calc, val);
		k = ft_rem(val, calc);
		q = 1;
		temp = ft_mult(val, k);
		calc->rem = ft_substract(calc->rem, temp);
		free(temp);
		calc->out = sjp(calc->out, k, 1, 1);
	}
	free(calc->rem);
	k = calc->out;
	free(calc);
	free(val);
	return (k);
}
