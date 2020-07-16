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

void		parse_ants(t_lem_in **lem_in, int fd)   // нет необходимости передовать через двой указатель
{
	char		*line;                             // Добавить line = NULL

	if ((get_next_line(fd, &line)))                // else  terminate(ошибкой что не отработал GNL)
	{
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
	room->output_links = 0;
	room->input_links = 0;
	room->next = NULL;
	ft_strsplit_free(&words);
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

// хочу подумать как ниже сделать рефакторинг

void		parse_room(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp)
{
	int			roomtype;
	t_room		*room;
	int res;


	roomtype = 2;
	while ((*tmp || ((*tmp) = read_line(input, fd))) &&         //   первое условие *tmp лишнее
	(res = is_command((*tmp)->data)                                   // записать результат выполнения как макросы START_END и (ROOM), чтобы второй раз в цикле не пересчитывать эти функции
	|| is_comment((*tmp)->data) || is_room((*tmp)->data)))
	{
		//printf("(*tmp)->data %s\n", (*tmp)->data);
		if (is_command((*tmp)->data) == 1)                 // тогда будет if (res == COMMAND)
			roomtype = get_type((*tmp)->data);                      // функция не выдаст ответ 2 можно в самой функции это поправить
		else if (is_room((*tmp)->data) == 1)                       // тогда будет if (res == ROOM)
		{
			room = create_room((*tmp)->data, roomtype);
			add_room(lem_in, room);
			validate_room(lem_in, room);
			roomtype = 2;
		}
		else
			roomtype = 2;
		if ((roomtype == 1 && lem_in->start) || (roomtype == 3 && lem_in->end))
		    terminate(ERR_ROOM_PARSING);
		(*tmp) = NULL;                                          // ощущение что free(tmp)
	}
}
