/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:07:46 by kysgramo          #+#    #+#             */
/*   Updated: 2019/12/02 15:25:42 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	clean_mult(t_mult *mult)
{
	free(mult->zero);
	free(mult->stra);
	free(mult->strb);
	free(mult);
}

void	clean_sum(t_sum *sum)
{
	free(sum->carryc);
	free(sum);
}

void	free_float_params(t_p *params)
{
	params->outpos = ft_strdup("");
	params->outneg = ft_strdup("");
	params->zero = "0";
	params->ten = "10";
	params->one = "1";
}

char	*sjp(char *s1, char *s2, int i, int j)
{
	int		len1;
	int		len2;
	char	*str;

	str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	len1 = 0;
	while (s1[len1])
	{
		str[len1] = s1[len1];
		len1++;
	}
	len2 = 0;
	while (s2[len2])
	{
		str[len1] = s2[len2];
		len1++;
		len2++;
	}
	str[len1] = '\0';
	if (i)
		free(s1);
	if (j)
		free(s2);
	return (str);
}

char	*ft_strsubf(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	sub = ft_strnew(len);
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	free(s);
	return (sub);
}
