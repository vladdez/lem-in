/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:11:21 by kysgramo          #+#    #+#             */
/*   Updated: 2020/02/25 14:11:23 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int		ft_words(char *s, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (s[i] != c)
	{
		i++;
		j++;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			j++;
		i++;
	}
	return (j);
}
