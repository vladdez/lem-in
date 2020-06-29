/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:02:17 by kysgramo          #+#    #+#             */
/*   Updated: 2020/06/29 13:02:22 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void		parse_ants(t_lem_in **lem_in, int fd)
{
	char		*line;

	if ((get_next_line(fd, &line)))
	{
		//printf("%s\n", line);
		if (ft_isint(line) == 1)
		{
			(*lem_in)->ant_num = ft_atoi(line);
			if ((*lem_in)->ant_num <= 0)
				terminate(ERR_ANTS_NUM_PARSING);
		}
		else
			terminate(ERR_ANTS_NUM_PARSING);
		free(line);
	}
}

int			get_type(char *line)
{
	int i;

	
	if (!ft_strcmp(line, "##start"))
		i = 1;
	else if (!ft_strcmp(line, "##end"))
		i = 3;
	else
		i = 2;
	printf("g %s %d\n", line, i);
	return (i);
	
}

t_room		*create_room(char *line, int roomtype)
{
	t_room		*room;
	char		**words;

	if (!(words = ft_strsplit(line, ' ')))
		terminate(ERR_ROOM_INIT);
	if (!(room = (t_room *)ft_memalloc(sizeof(t_room))))
		terminate(ERR_ROOM_INIT);
	if (!(room->name = ft_strdup(words[0])))
		terminate(ERR_ROOM_INIT);
	room->x = ft_atoi(words[1]);
	room->y = ft_atoi(words[2]);
	room->type = roomtype;
	printf("n %s\n", room->name);
	printf("t %d\n\n", roomtype);
	return (room);
}

void		add_room(t_lem_in *lem_in, t_room *room)
{
	t_room *tmp;

	if ((tmp = lem_in->rooms))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = room;
	}
	else
		lem_in->rooms = room;
	if (room->type == 1)
		lem_in->start = room;
	else if (room->type == 3)
		lem_in->end = room;
}

void		parse_room(t_lem_in *lem_in, int fd, t_line **input)
{
	int			roomtype;
	t_room		*room;

	roomtype = 2;
	while (((*input) = read_line(input, fd)))
	{
		printf("%s\n", (*input)->data);
		if (is_command((*input)->data) == 1)
		{
				roomtype = get_type((*input)->data);
			printf("tt %d\n\n", roomtype);
		}
		else if (is_room((*input)->data) == 1)
		{
			room = create_room((*input)->data, roomtype);
			roomtype = 2;
			add_room(lem_in, room);
		}
		else
			roomtype = 2;
	}
}
