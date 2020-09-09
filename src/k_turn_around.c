//
// Created by Brandy Hugo on 9/8/20.
//

#include "../inc/lem_in.h"

// from next_room to START
void    change_link_direction2(t_room *room, char *link_name)
{
	t_node *tmp;

	tmp = room->link;
	while(ft_strcmp(tmp->node, link_name) != 0)
		tmp = tmp->next;
	if (tmp->direction == BOTH_STREAM)    // всегда ли это поворот будет c таким значением
		tmp->direction = DOWNSTREAM;
	else if (tmp->direction == UPSTREAM)
		tmp->direction = DOWNSTREAM;
	else
		tmp->direction = UPSTREAM;
}

// from START to next_room
void    change_link_direction(t_room *room, char *link_name)
{
	t_node *tmp;

	tmp = room->link;
	while(ft_strcmp(tmp->node, link_name) != 0)
		tmp = tmp->next;
	if (tmp->direction == BOTH_STREAM)    // // всегда ли это поворот будет c таким значением
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

void    amend_links_in_direction_from_start(char *room_name, char *link_name, t_hashtable *ht)
{
    t_room *room;

	room = find_room_in_hashtable(room_name, ht);
	change_link_price(room, link_name);
	change_link_direction(room, link_name);
}

void    amend_links_in_direction_from_end(char *room_name, char *link_name, t_hashtable *ht)
{
	t_room *room;

	room = find_room_in_hashtable(room_name, ht);
	change_link_price(room, link_name);
	change_link_direction2(room, link_name);
}

void    turn_around_links(t_lem_in *lem_in, t_path *path)
{
	t_path *tmp;
	t_room *current_room;

	tmp = path;
	while (ft_strcmp(tmp->name, lem_in->end->room_name) != 0)
	{
		amend_links_in_direction_from_start(tmp->name, tmp->next->name, lem_in->ht_rooms);
		amend_links_in_direction_from_end(tmp->next->name, tmp->name, lem_in->ht_rooms);
		tmp = tmp->next;
	}
}
