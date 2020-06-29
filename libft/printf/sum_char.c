/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:51:57 by kysgramo          #+#    #+#             */
/*   Updated: 2019/11/23 16:26:07 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_sum	*create_sum(void)
{
	t_sum *sum;

	if (!(sum = (t_sum *)malloc(sizeof(t_sum))))
		return (NULL);
	sum->carryc = ft_strnew(1);
	sum->carry = 0;
	sum->s = 0;
	sum->l = 0;
	return (sum);
}

t_sum	*subloop(size_t longest, t_sum *sum)
{
	unsigned int	temp;

	temp = sum->carry;
	if (sum->l != 0)
	{
		temp = temp + (sum->stra[sum->l - 1] - '0');
		sum->l--;
	}
	if (sum->s != 0)
	{
		temp = temp + (sum->strb[sum->s - 1] - '0');
		sum->s--;
	}
	if (temp >= 10)
		sum->carry = temp / 10;
	else
		sum->carry = 0;
	if (temp >= 10)
		temp = temp % 10;
	sum->out[longest - 1] = temp + '0';
	return (sum);
}

char	*sum_loop(char *stra, char *strb, t_sum *sum)
{
	size_t			longest;

	sum->l = ft_strlen(stra);
	sum->s = ft_strlen(strb);
	longest = (sum->l >= sum->s) ? sum->l : sum->s;
	sum->out = ft_strnew(longest);
	sum->stra = stra;
	sum->strb = strb;
	while (longest != 0)
	{
		sum = subloop(longest, sum);
		longest--;
	}
	if (sum->carry > 0)
	{
		sum->carryc[0] = sum->carry + '0';
		sum->out = sjp("1", sum->out, 0, 1);
	}
	return (sum->out);
}

char	*sumneg(char *strb, int diff)
{
	if (diff > 0)
		while (diff != 0)
		{
			strb = sjp(strb, "0", 1, 0);
			diff--;
		}
	return (strb);
}

char	*ft_sum(char *stra, char *strb, int sw, int kek)
{
	char			*out;
	t_sum			*sum;
	int				diff;
	int				lena;
	int				lenb;

	lena = ft_strlen(stra);
	lenb = ft_strlen(strb);
	diff = (lena >= lenb) ? lena : lenb;
	diff = diff - ((lena >= lenb) ? lenb : lena);
	sum = create_sum();
	if (sw == 1)
		strb = sumneg(strb, diff);
	out = sum_loop(stra, strb, sum);
	if (kek == 1)
		free(stra);
	else if (kek == 2)
	{
		free(stra);
		free(strb);
	}
	else if (kek == 3)
		free(strb);
	clean_sum(sum);
	return (out);
}
