/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 12:59:24 by kysgramo          #+#    #+#             */
/*   Updated: 2020/06/29 12:59:33 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		is_room_name(char *str)
{
	if (str && ft_strlen(str))
	{
		if (str[0] != 'L' && str[0] != '#')
			return (1);
	}
	return (0);
}

int		is_room(char *str)
{
	char	**words;
	int		q;
	char	*s;
	int		res;

	res = 0;
	if (str)
	{
		s = ft_strdup(str);
		q = ft_words(s, ' ');
		if (!(words = ft_strsplit(str, ' ')))
			terminate(ERR_ROOM_PARSING);
		free(s);
		if (q == 3)
		{
			if (is_room_name(words[0]) && ft_isint(words[1])
			&& ft_isint(words[2]))
				res = 1;
			ft_strsplit_free(&words);
			return(res);
		}
		ft_strsplit_free(&words);
	}
	return (res);
}

int		is_command(char *str)
{
	if (str)
	{
		if (ft_strlen(str) >= 2
			&& !ft_strncmp(str, "##", 2))
			return (1);
	}
	return (0);
}

int		is_comment(char *str)
{
	if (str)
	{
		if (ft_strlen(str) >= 1 && !is_command(str)
		&& !ft_strncmp(str, "#", 1))
			return (1);
	}
	return (0);
}

int		ft_isint(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != '\0')
	{
		if (i == 0)
		{
			if (!((tmp[i] >= '0' && tmp[i] <= '9') ||
			tmp[i] == '-'))
				return (0);
		}
		else if (!(tmp[i] >= '0' && tmp[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
