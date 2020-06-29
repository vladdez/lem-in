/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:44:48 by kysgramo          #+#    #+#             */
/*   Updated: 2019/11/23 17:35:48 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_subs	*create_subs(void)
{
	t_subs *subs;

	if (!(subs = (t_subs *)malloc(sizeof(t_subs))))
		return (NULL);
	subs->carry = 0;
	subs->rem = 0;
	subs->temp = 0;
	subs->stra = "\0";
	subs->strb = "\0";
	subs->l = 0;
	subs->s = 0;
	subs->out = ft_strnew(0);
	subs->remc = "\0";
	return (subs);
}

char	*ft_zerotrim(t_subs *subs)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	j = 0;
	if (!subs->out)
		return (NULL);
	len = ft_strlen(subs->out);
	while (subs->out[i] == '0')
		i++;
	if (i == len)
	{
		free(subs->out);
		return (ft_strdup("0"));
	}
	new = ft_strnew((len - i));
	while (i < len)
	{
		new[j++] = subs->out[i++];
		new[j] = '\0';
	}
	free(subs->out);
	return (new);
}

char	*substr_loop(t_subs *subs, char *out)
{
	subs->rem = 0;
	subs->temp = 0;
	subs->temp -= subs->carry;
	if (subs->l != 0)
	{
		subs->temp = subs->temp + (subs->stra[subs->l - 1] - '0');
		subs->l--;
	}
	if (subs->s != 0)
	{
		subs->temp = subs->temp - (subs->strb[subs->s - 1] - '0');
		subs->s--;
	}
	if (subs->temp < 0)
	{
		subs->carry = 1;
		subs->rem = 10 + subs->temp;
		subs->temp = subs->rem;
	}
	else
		subs->carry = 0;
	subs->remc = ft_strnew(1);
	subs->remc[0] = subs->temp + '0';
	out = sjp(subs->remc, out, 1, 1);
	return (out);
}

char	*ft_substract(char *stra, char *strb)
{
	size_t	longest;
	t_subs	*subs;
	char	*s;

	subs = create_subs();
	subs->l = ft_strlen(stra);
	subs->s = ft_strlen(strb);
	if (subs->l >= subs->s)
		longest = subs->l;
	else
	{
		free(stra);
		return (NULL);
	}
	subs->stra = stra;
	subs->strb = strb;
	while (longest != 0)
	{
		subs->out = substr_loop(subs, subs->out);
		longest--;
	}
	s = ft_zerotrim(subs);
	free(subs->stra);
	free(subs);
	return (s);
}
