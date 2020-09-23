//
// Created by Brandy Hugo on 9/23/20.
//
#include "../inc/lem_in.h"

t_path    *put_belmon_ford_to_the_path(t_lem_in *lem_in, t_queue_bf *belmon_ford)
{
	t_path **tmp_path;
	t_path *point_path;
	t_room *tmp_room;
	int i;

	i = 0;
	tmp_path = lem_in->paths;
	while (tmp_path[i] != NULL)
		i++;
	tmp_path[i] = create_one_path(lem_in->end);
	belmon_ford = belmon_ford->parrent;
	while (belmon_ford->parrent != NULL)
	{
		tmp_room = find_room_with_type_in_hashtable(belmon_ford->room_name, belmon_ford->type_room, lem_in->ht_rooms);
		point_path = create_one_path(tmp_room);
		point_path->typeroom = belmon_ford->type_room;
		point_path->next = tmp_path[i];
		tmp_path[i] = point_path;
		belmon_ford = belmon_ford->parrent;
	}
	point_path = create_one_path(lem_in->start);
	point_path->next = tmp_path[i];
	tmp_path[i] = point_path;
	lem_in->path_num++;
	return (tmp_path[i]);
}