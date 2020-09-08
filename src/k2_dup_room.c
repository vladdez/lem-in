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

t_node   *find_after_room_in_path(char *room_name, t_path *path)
{
	t_node *tmp;

	tmp = path;
	while(ft_strcmp(room_name, tmp->next) != 0)
		tmp = tmp->next;
	return (tmp->next);
}

/*t_node   *find_before_room_in_path(char *room_name, t_path *path)
{
	t_node *tmp;
	t_node *lagged_tmp;

	lagged_tmp = path;
	tmp = lagged_tmp->next;
	while(ft_strcmp(room_name, tmp->next) != 0)
	{
		lagged_tmp = lagged_tmp->next;
		tmp = tmp->next;
	}
	return (lagged_tmp);
}*/

void    replace_link_from_in_to_out(t_room *room_in, t_room *room_out)
{

}

void    classify_links_between_in_and_out(t_room *room_in, t_room *room_out, t_path *path)
{
	//t_node *before_room;
	t_node *after_room;
	t_node *tmp;

	//before_room = find_before_room_in_path(room_in->room_name, path);
	after_room = find_after_room_in_path(room_in->room_name, path);
	tmp = room_in->link;
	while(tmp)
	{
		if (ft_strcmp(after_room, tmp->node))
			replace_link_from_in_to_out(room_in, room_out);
	}
}

void    create_and_classify_links(t_room *room_in, t_room *room_out, t_path *path)
{
	t_node  *tmp;

	create_links_with_zero_price(room_in, room_out);
	tmp = room_in->link;
	while(tmp)
	{
		if (tmp->price == -1)
			classify_links_between_in_and_out(room_in, room_out, path);
		tmp = tmp->next;
	}
}

void    create_room_out_and_classify_links(t_room *room_in, t_path *path)
{
	t_room *room_out;

	room_out = create_room_out(room_in);
	create_and_classify_links(room_in, room_out, path);
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
		create_room_out_and_classify_links(current_room, path);
		tmp = tmp->next;
	}
}