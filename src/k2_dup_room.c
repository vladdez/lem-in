//
// Created by Brandy Hugo on 9/8/20.
//
#include "../inc/lem_in.h"

t_room   *create_room_dup(char *name)
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
	tmp->next = create_room_dup(room->room_name);   // free
	tmp = tmp->next;
	return (tmp);
}

void	add_link_with_zero_price(t_node *link, char *toward)
{
	t_node	*tmp;

	tmp = link;
	if (tmp->node == NULL)
		tmp->node = toward;
	else
	{
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				tmp->next = neighbour_init();
				tmp = tmp->next;
				tmp->node = toward;
				break ;
			}
			tmp = tmp->next;
		}
	}
	tmp->direction = BOTH_STREAM;
	tmp->price = ZERO;
	tmp->next = NULL;
}


void create_links_with_zero_price(t_room *room_in, t_room *room_out)
{
	add_link_with_zero_price(room_in->link, room_out->room_name);
	add_link_with_zero_price(room_out->link, room_in->room_name);
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
void    move_first_link_of_room_in(t_room *in, t_room *out, char *link_name)
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
		move_first_link_of_room_in(in, out, link_name);
	else
		move_not_first_link_of_room_in(in, out, link_name);
}

void    move_link(t_room *in, t_room *out, char *link_name)
{
	t_room *tmp;
	// найти линк  и перенести в аут
	move_link_to_room_out(in, out, link_name);
	// найти в команту по имени линка и перенести связь из инт в  аут - вроде такого делать не надо !!!!
}

void    split_link_for_room_out(t_room *out, t_node *link_to_copy)
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
	}
	tmp->node = link_to_copy->node;
	tmp->price = link_to_copy->price;
	tmp->direction = DOWNSTREAM;
}

void    create_and_classify_links(t_room *room_in, t_room *room_out, t_hashtable *ht)
{
	t_node  *tmp;

	tmp = room_in->link;
	while(tmp)
	{
		if (tmp->price == MINUS_ONE && tmp->direction == UPSTREAM)
			move_link(room_in, room_out, tmp->node);
		if (tmp->price == 1)
		{
			tmp->direction = UPSTREAM;
			split_link_for_room_out(room_out, tmp);
		}
		tmp = tmp->next;
	}
	create_links_with_zero_price(room_in, room_out);
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
		current_room = find_room_in_hashtable(tmp->name, lem_in->ht_rooms);
		current_room->in_out = IN;
		create_room_out_and_classify_links(current_room, lem_in->ht_rooms);
		tmp = tmp->next;
	}
}