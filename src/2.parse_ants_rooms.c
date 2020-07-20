/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:02:17 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/06 17:03:44 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void		parse_ants(t_lem_in *lem_in, int fd)
{
	char		*line;

	line = NULL;
	if ((get_next_line(fd, &line)))
	{
		if (ft_isint(line) == 1)
		{
			lem_in->ant_num = ft_atoi(line);
			if (lem_in->ant_num <= 0)
				terminate(ERR_ANTS_NUM_PARSING);
		}
		else
			terminate(ERR_ANTS_NUM_PARSING);
		free(line);
	}
}

int			get_type(char *tmp)
{
	int	i;

	if (!ft_strcmp(tmp, "##start"))
		i = 1;
	else if (!ft_strcmp(tmp, "##end"))
		i = 3;
	else
		i = 2;
	return (i);
}

t_room		*create_room(char *tmp, int roomtype)
{
	t_room		*room;
	char		**words;

	if (!(words = ft_strsplit(tmp, ' ')))
		terminate(ERR_ROOM_INIT);
	if (!(room = (t_room *)malloc(sizeof(t_room))))
		terminate(ERR_ROOM_INIT);
	if (!(room->name = ft_strdup(words[0])))
		terminate(ERR_ROOM_INIT);
	room->x = ft_atoi(words[1]);
	room->y = ft_atoi(words[2]);
	room->type = roomtype;
	room->bfs_level = -1;
	//room->visited = 0;
	room->output_links = 0;
	room->input_links = 0;
	room->nei = NULL;
	room->next = NULL;
	ft_strsplit_free(&words);
	return (room);
}

void		check_room(t_lem_in *lem_in, t_room *room)
{
	if (room->type == 1)
		lem_in->start = room;
	else if (room->type == 3)
		lem_in->end = room;
}

void		parse_room(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp)
{
	int			roomtype;
	t_room		*tmpr;
	int			r;
	int			i;

	r = 1;
	i = -1;
	roomtype = 2;
	while (((*tmp) = read_line(input, fd)) && ((r = iswhat((*tmp)->data)) > 0))
	{
		if (r == 1)
			roomtype = get_type((*tmp)->data);
		else if (r == 2)
		{
			i = hash_fun_room((*tmp)->data);
			if (lem_in->hash_table[i] == NULL)
				lem_in->hash_table[i] = create_room((*tmp)->data, roomtype);
			else
			{
				tmpr = create_room((*tmp)->data, roomtype);
				tmpr->next = lem_in->hash_table[i];
				lem_in->hash_table[i] = tmpr;
			}
			check_room(lem_in, lem_in->hash_table[i]);
			validate_room(lem_in, lem_in->hash_table[i]);
			roomtype = 2;
		}
		else
			roomtype = 2;
		if ((roomtype == 1 && lem_in->start)
			|| (roomtype == 3 && lem_in->end))
			terminate(ERR_ROOM_PARSING);
		(*tmp) = NULL;
	}
	if (!(lem_in->end))
        terminate(ERR_ROOM_PARSING);
}
