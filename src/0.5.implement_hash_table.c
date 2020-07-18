/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.implement_hash_table.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 16:52:55 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/17 16:53:22 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		hash_fun(char *room_name)
{
	int		value;
	int		i;

	value = 0;
	i = 0;
	while (room_name[i])
	{
		value = value + room_name[i] * 41;
		i++;
	}
	return (value % TABLEN);
}

int		hash_fun_room(char *str)
{
	int		value;
	int		i;
	char	*d;
	char	*room_name;

	d = str;

	d = ft_strchr(d, ' ');
	if (!(room_name = ft_strsub(str, 0, d - str)))
		terminate(ERR_ROOM_PARSING);
	value = 0;
	i = 0;
	while (room_name[i])
	{
		value = value + room_name[i] * 41;
		i++;
	}
	free(room_name);
	return (value % TABLEN);
}

void		create_hash_table(t_lem_in *lem_in)
{
	int			i;

	i = 0;
	lem_in->hash_table = (t_room **)malloc(sizeof(t_room *) * TABLEN);
	while (i < TABLEN)
	{
		lem_in->hash_table[i] = NULL;
		i++;
	}
}
