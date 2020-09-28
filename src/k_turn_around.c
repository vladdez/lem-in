//
// Created by Brandy Hugo on 9/8/20.
//

#include "../inc/lem_in.h"

// from next_room to START
void    change_link_direction2(t_room *room, char *link_name, int link_typeroom)
{
	t_node *tmp;

	tmp = room->link;
	while (tmp)
	{
		if (ft_strcmp(tmp->node, link_name) == 0 && tmp->type_room == link_typeroom)
			break;
		tmp = tmp->next;
	}
	if (tmp->direction == BOTH_STREAM)    // всегда ли это поворот будет c таким значением
		tmp->direction = DOWNSTREAM;
	else if (tmp->direction == UPSTREAM)
		tmp->direction = DOWNSTREAM;
	else
		tmp->direction = UPSTREAM;
}

// from START to next_room
void    change_link_direction(t_room *room, char *link_name, int link_typeroom)
{
	t_node *tmp;

	tmp = room->link;
	while (tmp)
	{
		if (ft_strcmp(tmp->node, link_name) == 0 && tmp->type_room == link_typeroom)
			break;
		tmp = tmp->next;
	}
	if (tmp->direction == BOTH_STREAM)    // // всегда ли это поворот будет c таким значением
		tmp->direction = UPSTREAM;
	else if (tmp->direction == UPSTREAM)
		tmp->direction = DOWNSTREAM;
	else
		tmp->direction = UPSTREAM;
}


void    delete_dup_links_not_on_the_way_but_neibours(t_room *room_tmp, char *name_of_link_to_delete, t_hashtable *ht)
{
	t_room *tmp;

	delete_dup_link(room_tmp, name_of_link_to_delete, OUT);                           // удаление  соседних дублированных линков и надо понять что с  их направлением  делать так оставялть линк как есть не вариант думаю вернуть изначальное направление
	tmp = find_room_with_type_in_hashtable(name_of_link_to_delete, OUT, ht);
	delete_dup_link(tmp, room_tmp->room_name, room_tmp->in_out);
	change_link_direction(room_tmp, name_of_link_to_delete, IN);
	tmp = find_room_with_type_in_hashtable(name_of_link_to_delete, IN, ht);
	change_link_direction2(tmp, room_tmp->room_name, room_tmp->in_out);
}

void    find_and_delete_dup_links(t_path *lagged, t_path *tmp, t_path *next, t_hashtable *ht)
{
	 t_room *room_tmp;
	 t_node *link_tmp;
	 t_node *link_tmp2;
	 char *seeking_link;

	 room_tmp = find_room_with_type_in_hashtable(tmp->name, tmp->typeroom, ht);
	 link_tmp = room_tmp->link;
	 while (link_tmp)
	 {
	 	if (ft_strcmp(link_tmp->node, lagged->name) != 0 && ft_strcmp(link_tmp->node, next->name) != 0)
	    {
		    seeking_link = link_tmp->node;
		    link_tmp2 = link_tmp->next;
		    while (link_tmp2)
		    {
			    if (ft_strcmp(link_tmp2->node, seeking_link) == 0)
			    {
				    delete_dup_links_not_on_the_way_but_neibours(room_tmp, seeking_link, ht);
				    break;
			    }
		    	link_tmp2 = link_tmp2->next;
		    }
	    }
	 	link_tmp = link_tmp->next;
	 }

}

void    analyse_dup_links_not_on_the_way_but_neibours(t_path *path, t_lem_in *lem_in)
{
	t_path *tmp;
	t_path *lagged_tmp;

	lagged_tmp = path;
	tmp = lagged_tmp->next;
	while (ft_strcmp(tmp->name, lem_in->end->room_name) != 0)
	{
		find_and_delete_dup_links(lagged_tmp, tmp, tmp->next, lem_in->ht_rooms);
		tmp = tmp->next;
	}
}

void    change_link_price(t_room *room, char *link_name, int link_typeroom)
{
	t_node *tmp;

	tmp = room->link;
	while (tmp)
	{
			if (ft_strcmp(tmp->node, link_name) == 0 && tmp->type_room == link_typeroom)
				break;
		tmp = tmp->next;
	}
	tmp->price == ONE ? (tmp->price = MINUS_ONE) : (tmp->price = ONE);
}

void    amend_links_in_direction_from_start(t_path *room, t_path *link, t_hashtable *ht)
{
    t_room *tmp;

	tmp = find_room_with_type_in_hashtable(room->name, room->typeroom, ht);
	change_link_price(tmp, link->name, link->typeroom);
	change_link_direction(tmp, link->name, link->typeroom);
	if (check_condition_to_delete_dup_links(tmp->in_out, link->typeroom) == 1)         		//анализ линков и удалени дублированных линков при повороте
		delete_dup_link_in_both_room(tmp, link, ht);

}

void    amend_links_in_direction_from_end(t_path *room, t_path *link, t_hashtable *ht)
{
	t_room *tmp;

	tmp = find_room_with_type_in_hashtable(room->name, room->typeroom, ht);
	change_link_price(tmp, link->name, link->typeroom);
	change_link_direction2(tmp, link->name, link->typeroom);
}

void    turn_around_links(t_lem_in *lem_in, t_path *path)
{
	t_path *tmp;

	tmp = path;
	while (ft_strcmp(tmp->name, lem_in->end->room_name) != 0)
	{
		if (ft_strcmp(tmp->name, tmp->next->name) != 0)
		{
			amend_links_in_direction_from_start(tmp, tmp->next, lem_in->ht_rooms);
			amend_links_in_direction_from_end(tmp->next, tmp, lem_in->ht_rooms);
		}
		tmp = tmp->next;
	}
	analyse_dup_links_not_on_the_way_but_neibours(path, lem_in);
}
