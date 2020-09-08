//
// Created by Brandy Hugo on 9/8/20.
//


#include "../inc/lem_in.h"


void    change_link_direction(t_room *room, char *link_name)
{
	t_node *tmp;

	tmp = room->link;
	while(ft_strcmp(tmp->node, link_name) != 0)
		tmp = tmp->next;
	if (tmp->direction == BOTH_STREAM)    // всегда ли это поворот будет
		tmp->direction = UPSTREAM;
	else if (tmp->direction == UPSTREAM)
		tmp->direction = DOWNSTREAM;
	else
		tmp->direction = UPSTREAM;
}

void    change_link_price(t_room *room, char *link_name)
{
	t_node *tmp;

	tmp = room->link;
	while(ft_strcmp(tmp->node, link_name) != 0)
		tmp = tmp->next;
	tmp->price == ONE ? (tmp->price = MINUS_ONE) : (tmp->price = ONE);
}

void    turn_around_links(t_lem_in *lem_in, t_path *path)
{
	t_path *tmp;
	t_room *current_room;

	tmp = path;
	while (ft_strcmp(tmp->name, lem_in->end->room_name) != 0)
	{
		current_room = find_room_in_hashtable(tmp->name, lem_in->ht_rooms);
		change_link_price(current_room, tmp->next->name);
		change_link_direction(current_room, tmp->next->name);
		tmp = tmp->next;
	}
}


/// !!!! поменять напреление и у входа  и  у выхода линка!!!!!!!!!!!!!!!