/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:27:53 by klaurine          #+#    #+#             */
/*   Updated: 2019/08/31 19:26:54 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;

	if (!(s2 = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	s2[n] = '\0';
	ft_strncpy(s2, s1, n);
	return (s2);
}
