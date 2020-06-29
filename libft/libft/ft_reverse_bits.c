/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_bits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 18:38:31 by klaurine          #+#    #+#             */
/*   Updated: 2019/08/31 18:10:20 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	ft_reverse_bits(unsigned char octet)
{
	int				t;
	unsigned char	a;

	t = 0;
	while (t <= 7)
	{
		a = a | ((octet >> t) & 1) << (7 - t);
		t++;
	}
	return (a);
}
