/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 12:59:24 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/20 19:05:04 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

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

	if (str)
	{
		if (!(s = ft_strdup(str)))
			terminate(ERR_ROOM_PARSING);
		q = ft_words(s, ' ');
		free(s);
		if (q == 3)
		{
			if (!(words = ft_strsplit(str, ' ')))
				terminate(ERR_ROOM_PARSING);
			if ((is_room_name(words[0])) && ft_isint(words[1])
					&& ft_isint(words[2]))
			{
				ft_strsplit_free(&words);
				return (ROOM);
			}
			ft_strsplit_free(&words);
		}
	}
	return (0);
}

int		is_command(char *str)
{
	if (str)
	{
		if ((ft_strncmp(str, "##start", 7) == 0) ||
				(ft_strncmp(str, "##end", 5)) == 0)
			return (COMMAND);
	}
	return (0);
}

int		is_comment(char *str)
{
	if (str)
	{
		if (ft_strlen(str) >= 1 && !is_command(str)
				&& !ft_strncmp(str, "#", 1))
			return (COMMENT);
	}
	return (0);
}

int		ft_isint(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != '\0')
	{
		if (!(tmp[i] >= '0' && tmp[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
