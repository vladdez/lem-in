//
// Created by Brandy Hugo on 9/23/20.
//

#include "../inc/lem_in.h"

t_queue_bf	*init_belmon_ford(void)
{
	t_queue_bf *belmon_ford;

	if (!(belmon_ford = malloc(sizeof(t_queue_bf) * 1)))
		terminate(ERR_ALLOCATION);
	belmon_ford->type_room = IN_OUT;
	belmon_ford->room_name = NULL;
	belmon_ford->accumulated_value = 0;
	belmon_ford->parrent = NULL;
	belmon_ford->next = NULL;
	return (belmon_ford);
}

void put_start_data(t_queue_bf *belmon_ford, t_room* start)
{
	if (!(belmon_ford->room_name = ft_strdup(start->room_name)))
		terminate(ERR_ALLOCATION);
}

void put_data_in_queue(t_queue_bf *tmp_queue, t_queue_bf *belmon_ford, t_node *link)
{
	if (!(tmp_queue->room_name  = ft_strdup(link->node)))
		terminate(ERR_ROOM_INIT);
	tmp_queue->type_room = link->type_room;
	tmp_queue->parrent = belmon_ford;
	tmp_queue->accumulated_value = belmon_ford->accumulated_value + link->price;

}

t_queue_bf *find_end_of_queue(t_queue_bf *belmon_ford)
{
	t_queue_bf *tmp;

	tmp = belmon_ford;
	while(tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int     check_conditions_for_belmon_ford_queue(t_node *link, t_queue_bf *belmon_ford, t_room *room, char *start_name)
{
	if (link->direction == UPSTREAM)
		return (0);
	if (belmon_ford->parrent != NULL && ft_strcmp(link->node, belmon_ford->parrent->room_name) == 0)  // parrent
		return (0);
	if (ft_strcmp(link->node, room->room_name) == 0)  //  dub room
		return (0);
	if (ft_strcmp(link->node, start_name) == 0)  //  start room => cycle
		return (0);
	else
		return (1);
}

void    add_links_to_belmon_ford_queue(t_room *tmp_room, t_queue_bf *belmon_ford, char *start_name)
{
	t_node *tmp_link;
	t_queue_bf *tmp_queue;
	t_queue_bf *end_queue;
	int         i;

	i = 0;
	if (tmp_room != NULL && tmp_room->link != NULL && tmp_room->link->node != NULL)
	{
		tmp_link = tmp_room->link;
		end_queue = find_end_of_queue(belmon_ford);
		while (tmp_link)
		{
			if (check_conditions_for_belmon_ford_queue(tmp_link, belmon_ford, tmp_room, start_name)) //  1 - проходит, 0 - нет
			{
				tmp_queue = init_belmon_ford();
				put_data_in_queue(tmp_queue, belmon_ford, tmp_link);
				end_queue->next = tmp_queue;
				end_queue = end_queue->next;
				i++;
			}
			tmp_link = tmp_link->next;
		}
		if (i == 0)
		{
			tmp_link = tmp_room->link;
			while (tmp_link)
			{
				if (ft_strcmp(tmp_link->node, tmp_room->room_name) == 0) //   dub room
				{
					tmp_queue = init_belmon_ford();
					put_data_in_queue(tmp_queue, belmon_ford, tmp_link);
					end_queue->next = tmp_queue;
					break;
				}
				tmp_link = tmp_link->next;
			}
		}
	}
}

t_queue_bf    *algorithm_belmon_ford(t_lem_in *lem_in)
{
	t_queue_bf *belmon_ford;
	t_room *tmp;

	belmon_ford = init_belmon_ford();                                             // need to be freed
	put_start_data(belmon_ford, lem_in->start);
	while (belmon_ford != NULL && ft_strcmp(belmon_ford->room_name, lem_in->end->room_name) != 0)
	{
		tmp = find_room_with_type_in_hashtable(belmon_ford->room_name, belmon_ford->type_room, lem_in->ht_rooms);
		add_links_to_belmon_ford_queue(tmp, belmon_ford, lem_in->start->room_name);
		belmon_ford = belmon_ford->next;
		//printf("cycle");
	}
	// нужно продумать какой путь выбирать  что делать дальше если у нас есть еще end  как в примере в тетради
	return (belmon_ford);
}