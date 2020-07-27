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
	char	*d;
	int		i;
	char	*room_name;

	d = str;
	d = ft_strchr(d, ' ');
	if (!(room_name = ft_strsub(str, 0, d - str)))
		terminate(ERR_ROOM_PARSING);
	i = hash_fun(room_name);
	free(room_name);
	return (i);
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
