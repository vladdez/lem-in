/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:41:10 by kysgramo          #+#    #+#             */
/*   Updated: 2019/11/18 20:41:34 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_mult	*create_mult(void)
{
	t_mult *mult;

	if (!(mult = (t_mult *)malloc(sizeof(t_mult))))
		return (NULL);
	mult->zero = ft_strdup("0");
	mult->preout = "\0";
	mult->out = ft_strdup("0");
	mult->stra = "\0";
	mult->strb = "\0";
	mult->hereout = "\0";
	mult->longest = 0;
	mult->carry = 0;
	mult->i = 0;
	return (mult);
}

t_mult	*subloop_mult(t_mult *mult, size_t longest, size_t s, size_t l)
{
	unsigned int	temp;

	temp = 0;
	while (l != 0)
	{
		temp = (mult->stra[l - 1] - '0');
		temp = temp * (mult->strb[s - 1] - '0');
		temp = temp + mult->carry;
		if (temp >= 10)
		{
			mult->carry = temp / 10;
			temp = temp % 10;
		}
		else
			mult->carry = 0;
		mult->preout[longest - 1] = temp + '0';
		longest--;
		l--;
	}
	return (mult);
}

char	*mult_loop(size_t l, size_t s, t_mult *mult)
{
	char	*carryc;
	size_t	longest;

	longest = (l >= s) ? l : s;
	mult->preout = ft_strnew(longest);
	carryc = ft_strnew(1);
	mult = subloop_mult(mult, longest, s, l);
	if (mult->carry >= 10)
	{
		carryc[0] = '0' + (mult->carry % 10);
		mult->preout = sjp(carryc, mult->preout, 0, 1);
		mult->carry = mult->carry / 10;
	}
	else if (mult->carry > 0)
	{
		carryc[0] = mult->carry + '0';
		mult->preout = sjp(carryc, mult->preout, 0, 1);
	}
	free(carryc);
	return (mult->preout);
}

char	*ft_mult(char *stra, char *strb)
{
	t_mult	*mult;
	size_t	l;
	size_t	s;
	int		j;

	mult = create_mult();
	l = ft_strlen(stra);
	s = ft_strlen(strb);
	mult->stra = ft_strdup(stra);
	mult->strb = ft_strdup(strb);
	while (s != 0)
	{
		mult->hereout = mult_loop(l, s, mult);
		j = 0;
		while (mult->i != j)
		{
			mult->hereout = sjp(mult->hereout, mult->zero, 1, 0);
			j++;
		}
		mult->out = ft_sum(mult->out, mult->hereout, 0, 2);
		mult->i++;
		s--;
	}
	clean_mult(mult);
	return (mult->out);
}
