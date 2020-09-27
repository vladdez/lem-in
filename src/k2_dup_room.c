//
// Created by Brandy Hugo on 9/8/20.
//
#include "../inc/lem_in.h"

t_room   *create_room_out_dup(char *name)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		terminate(ERR_ROOM_INIT);
	if (!(room->room_name = ft_strdup(name)))
		terminate(ERR_ROOM_INIT);
	room->in_out = OUT;
	room->next = NULL;
	room->link = neighbour_init();
	room->bfs_visit = UNVISITED;         // do not care
	room->ek_visit = UNVISITED;           // do not care
	room->bfs_level = -1;               //  should i copy it ?
	room->outgoing_links = NULL;      // do not care
	room->incoming_links = NULL; // do not care
	room->cut = UNCUT; // do not care
	return (room);
}

t_room  *create_room_out(t_room *room)
{
	t_room *tmp;

	tmp = room;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_room_out_dup(room->room_name);   //  why not free
	tmp = tmp->next;
	return (tmp);
}

void	add_link_with_zero_price(t_node *link, char *toward)
{
	t_node	*tmp;

	tmp = link;
	if (tmp->node == NULL)
	{
		if (!(tmp->node = ft_strdup(toward)))
			terminate(ERR_ROOM_INIT);
	}
	else
	{
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				tmp->next = neighbour_init();
				tmp = tmp->next;
				if (!(tmp->node = ft_strdup(toward)))
					terminate(ERR_ROOM_INIT);
				break ;
			}
			tmp = tmp->next;
		}
	}
	tmp->direction = BOTH_STREAM;
	tmp->price = ZERO;
	tmp->next = NULL;
}


void    change_roomtype_to_in_and_direction(t_room *in, t_node *link, t_hashtable *ht)
{
	t_room *tmp;
	t_node *tmp_link;

	tmp = find_room_with_type_in_hashtable(link->node, link->type_room, ht);
	tmp_link = tmp->link;
	while (ft_strcmp(tmp_link->node, in->room_name) != 0)
		tmp_link = tmp_link->next;
	tmp_link->type_room = IN;
	tmp_link->direction = DOWNSTREAM;
}

void    change_roomtype_to_out(t_room *out, t_node *link, t_hashtable *ht)
{
	t_room *tmp;
	t_node *tmp_link;

	tmp = find_room_with_type_in_hashtable(link->node, link->type_room, ht);
	tmp_link = tmp->link;
	while (ft_strcmp(tmp_link->node, out->room_name) != 0)
		tmp_link = tmp_link->next;
	tmp_link->type_room = OUT;
}


void    change_roomtype_to_in_duprooms(t_room *out)
{
	t_node *tmp_link;

	tmp_link = out->link;
	while (ft_strcmp(tmp_link->node, out->room_name) != 0)
		tmp_link = tmp_link->next;
	tmp_link->type_room = IN;
}

void    change_roomtype_to_out_duprooms(t_room *in)
{
	t_node *tmp_link;

	tmp_link = in->link;
	while (ft_strcmp(tmp_link->node, in->room_name) != 0)
		tmp_link = tmp_link->next;
	tmp_link->type_room = OUT;
}

void create_links_with_zero_price(t_room *room_in, t_room *room_out)
{
	add_link_with_zero_price(room_in->link, room_out->room_name);
	change_roomtype_to_out_duprooms(room_in);   // // mistake
	add_link_with_zero_price(room_out->link, room_in->room_name);        // //  2 round mistake
	change_roomtype_to_in_duprooms(room_out);   // // mistake
}

void    find_place_for_link_in_room_out(t_room *out, t_node *tmp)
{
	t_node *tmp2;

	if (out->link->node == NULL)
		out->link = tmp;
	else
	{
		tmp2 = out->link;
		while (tmp2->next != NULL)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
}
void    move_not_first_link_of_room_in(t_room *in, t_room *out, char *link_name)
{
	t_node *tmp;
	t_node *lagged_tmp;

	lagged_tmp = in->link;
	tmp = in->link->next;
	while (ft_strcmp(tmp->node, link_name) != 0)
	{
		lagged_tmp = lagged_tmp->next;
		tmp = tmp->next;
	}
	lagged_tmp->next = tmp->next;
	tmp->next = NULL;
	find_place_for_link_in_room_out(out, tmp);
}

void    move_first_link_of_room_in(t_room *in, t_room *out)
{
	t_node *tmp;

	tmp = in->link;
	if (in->link->next != NULL)
		in->link = in->link->next;
	else
		in->link = NULL;
	tmp->next = NULL;
	find_place_for_link_in_room_out(out, tmp);
}

void    move_link_to_room_out(t_room *in, t_room *out, char *link_name)
{
	if (ft_strcmp(in->link->node, link_name) == 0)
		move_first_link_of_room_in(in, out);
	else
		move_not_first_link_of_room_in(in, out, link_name);
}


void    move_link(t_room *in, t_room *out, t_node *link, t_hashtable *ht)
{
	// найти линк у самой команты (она по дефолту in)  и перенести в аут
	move_link_to_room_out(in, out, link->node);
	// найти в команту по имени линка и обзначить связь что она входит в аут
	change_roomtype_to_out(out, link, ht);
}


void    create_link_dup(t_room *out, t_node *link_to_copy, t_hashtable *ht)
{
	t_room *tmp_room;
	t_node *tmp_link;

	tmp_room = find_room_with_type_in_hashtable(link_to_copy->node, link_to_copy->type_room, ht);
	tmp_link = tmp_room->link;
	while (tmp_link->next != NULL)
		tmp_link = tmp_link->next;
	tmp_link->next = neighbour_init();
	tmp_link = tmp_link->next;
	tmp_link->type_room = OUT;
	if (!(tmp_link->node = ft_strdup(out->room_name)))
		terminate(ERR_ALLOCATION);
	tmp_link->price = link_to_copy->price;
	tmp_link->direction = UPSTREAM;
}

void    split_link_for_room_out(t_room *out, t_node *link_to_copy, t_hashtable *ht)
{
	t_node *tmp;

	if (out->link->node == NULL)
		tmp = out->link;
	else
	{
		tmp = out->link;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = neighbour_init();
		tmp = tmp->next;
	}
	if (!(tmp->node = ft_strdup(link_to_copy->node)))
		terminate(ERR_ROOM_INIT);
	tmp->price = link_to_copy->price;
	tmp->direction = DOWNSTREAM;
	tmp->type_room = link_to_copy->type_room;
	create_link_dup(out, tmp, ht);// создаем вторую связь и сказать что она  входит в  аут
}

void    create_and_classify_links(t_room *in, t_room *out, t_hashtable *ht)
{
	t_node  *tmp;
	t_node  *tmp_next;

	tmp_next = NULL;
	tmp = in->link; // потому что room_in по дефолту
	while (tmp)
	{
		if (tmp->price == MINUS_ONE && tmp->direction == UPSTREAM)
		{
			if (tmp->next != NULL)
				tmp_next = tmp->next;
			move_link(in, out, tmp, ht);
			if (tmp_next != NULL)
				tmp = tmp_next;
		}
		if (tmp->price == MINUS_ONE && tmp->direction == DOWNSTREAM)
			change_roomtype_to_in_and_direction(in, tmp, ht);
		if (tmp->price == ONE && tmp->direction == BOTH_STREAM)
		{
			tmp->direction = UPSTREAM;
			change_roomtype_to_in_and_direction(in, tmp, ht);
			split_link_for_room_out(out, tmp, ht);
		}
		tmp = tmp->next;
	}
	create_links_with_zero_price(in, out);
}

void    create_room_out_and_classify_links(t_room *room_in, t_hashtable *ht)
{
	t_room *room_out;

	room_out = create_room_out(room_in);
	create_and_classify_links(room_in, room_out, ht);
}

void    dub_rooms(t_lem_in *lem_in, t_path *path)
{
	t_path *tmp;
	t_room *current_room;

	tmp = path->next;
	while (ft_strcmp(tmp->name, lem_in->end->room_name) != 0)
	{
		current_room = find_room_with_type_in_hashtable(tmp->name, tmp->typeroom, lem_in->ht_rooms);
		if (current_room->in_out == IN_OUT)
		{
			current_room->in_out = IN;
			create_room_out_and_classify_links(current_room, lem_in->ht_rooms);
		}
		tmp = tmp->next;
	}
}