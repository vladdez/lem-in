/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:12:37 by klaurine          #+#    #+#             */
/*   Updated: 2019/05/10 20:48:31 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		ft_wordss(char const *s, char c)
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

static char		*ft_return(char const *s, int i, char c)
{
	int		j;
	char	*str;

	j = i;
	while (s[j] != c && s[j])
		j++;
	if (!(str = (char *)malloc(sizeof(char) * (j - i + 1))))
		return (NULL);
	j = 0;
	while (s[i] && s[i] != c)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

static void		ft_free(char **array, int number)
{
	int i;

	i = 0;
	while (i < number)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = 0;
	if (!s || !(arr = (char **)malloc(sizeof(char *) * (ft_wordss(s, c) + 1))))
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!(arr[j] = ft_return(s, i, c)))
			{
				ft_free(arr, j);
				return (NULL);
			}
			j++;
			while (s[i] != c && s[i + 1])
				i++;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}
