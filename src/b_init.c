/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.1.init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 19:28:01 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/19 19:28:11 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_hashtable		*ht_create(void)
{
	t_hashtable	*ht_rooms;
	int			i;

	i = 0;
	if (!(ht_rooms = malloc(sizeof(t_hashtable))))
		terminate(ERR_ALLOCATION);
	if (!(ht_rooms->room = malloc(sizeof(t_room *) * TABLE_SIZE)))
		terminate(ERR_ALLOCATION);
	while (i < TABLE_SIZE)
		ht_rooms->room[i++] = NULL;
	return (ht_rooms);
}

t_coordinate	*coordinate_create(void)
{
	t_coordinate *coordinate;

	if (!(coordinate = malloc(sizeof(t_coordinate))))
		terminate(ERR_ALLOCATION);
	coordinate->room_name = NULL;
	coordinate->x = -1;
	coordinate->y = -1;
	coordinate->next = NULL;
	return (coordinate);
}

t_lem_in		*init_lem_in(void)
{
	t_lem_in	*lem_in;

	if (!(lem_in = (t_lem_in*)malloc(sizeof(t_lem_in))))
		terminate(ERR_ALLOCATION);
	lem_in->ants_start = 0;
	lem_in->ants_end = 0;
	lem_in->ant_num = 0;
	lem_in->edge_num = 0;
	lem_in->lines = 0;
	lem_in->room_num = 0;
	lem_in->path_num = 0;
	lem_in->start = NULL;
	lem_in->end = NULL;
	lem_in->coordinate = coordinate_create();
	lem_in->ht_rooms = ht_create();
	lem_in->mem = NULL;
	lem_in->bfs_used = 0;
	lem_in->ek_used = 1;
	return (lem_in);
}
