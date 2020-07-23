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
	if ((get_next_line(fd, &line)) > 0)
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
	else
	    terminate(ERR_ANTS_NUM_PARSING);
}

int			get_type(char *tmp)
{
    return !ft_strcmp(tmp, "##start") ? 1 : 3;
}

t_neighbours *neighbour_init()
{
    t_neighbours *link;

    if (!(link = malloc(sizeof(t_neighbours) * 1)))
        terminate(ERR_ALLOCATION);
    link->toward = NULL;
    link->next = NULL;
    return(link);
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
	room->output_links = 0;
	room->input_links = 0;
	room->next = NULL;
	room->link = neighbour_init();
	ft_strsplit_free(&words);
	return (room);
}

void		add_room(t_lem_in *lem_in, t_room *room)
{
    int  i;
    t_room *tmp;

    i = sum_ascii(room->name) % TABLE_SIZE;
    if (lem_in->hash_table->room[i] == NULL)
        lem_in->hash_table->room[i] = room;
    else
    {
        tmp = lem_in->hash_table->room[i];
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = room;
    }
}


void start_end(t_lem_in *lem_in, t_room *room, int roomtype)
{
    if (roomtype == 1)
        lem_in->start = room;
    if (roomtype == 3)
        lem_in->end = room;
}

void		parse_room(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp)
{
	int			roomtype;
	t_room		*room;
	int res;

	*input = NULL;
	roomtype = 2;
	res = 0;
	while (((*tmp) = read_line(input, fd)) &&
	((res = is_command((*tmp)->data)) || is_comment((*tmp)->data) || (res = is_room((*tmp)->data))))
	{
		if (res == COMMAND)
			roomtype = get_type((*tmp)->data);
		else if (res == ROOM)
		{
			room = create_room((*tmp)->data, roomtype);
			start_end(lem_in, room, roomtype);
			add_room(lem_in, room);
			validate_room(lem_in, room);                      // встроить в add_room
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
