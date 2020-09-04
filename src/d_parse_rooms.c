/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:02:17 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/19 16:56:35 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		get_type(char *tmp)
{
	return (!ft_strcmp(tmp, "##start") ? 1 : 3);
}

void	add_room(t_lem_in *lem_in, t_room *room)
{
	int		i;
	t_room	*tmp;

	i = sum_ascii(room->room_name);
	if (lem_in->ht_rooms->room[i] == NULL)
		lem_in->ht_rooms->room[i] = room;
	else
	{
		tmp = lem_in->ht_rooms->room[i];
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = room;
	}
}

void	start_end(t_lem_in *lem_in, t_room *room, int roomtype)
{
	if (roomtype == 1)
		lem_in->start = room;
	if (roomtype == 3)
		lem_in->end = room;
}

void	write_room_data(t_lem_in *lem_in, t_line **tmp, int roomtype)
{
	t_room		*room;

	room = create_room(lem_in->coordinate, (*tmp)->data);
	start_end(lem_in, room, roomtype);
	add_room(lem_in, room);
	validate_room(lem_in, room);
	lem_in->room_num++;
}

void	parse_room(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp)
{
	int	roomtype;
	int	res;

	*input = NULL;
	roomtype = 2;
	while (((*tmp) = read_line(input, fd)) &&
			(res = iswhat((*tmp)->data)))
	{
		if (res == COMMAND)
			roomtype = get_type((*tmp)->data);
		else if (res == ROOM)
		{
			write_room_data(lem_in, &(*tmp), roomtype);
			roomtype = 2;
		}
		else
			roomtype = 2;
		if ((roomtype == 1 && lem_in->start) || (roomtype == 3 && lem_in->end))
			terminate(ERR_ROOM_PARSING);
		(*tmp) = NULL;
	}
	if (!lem_in->start || !lem_in->end)
		terminate(ERR_START_END_ROOM);
}
