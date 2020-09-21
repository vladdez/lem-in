//
// Created by Ирина Деева on 07.09.2020.
//

#include "../inc/lem_in.h"

typedef struct s_queue_bf
{
	char    *room_name;
	int     accumulated_value;
	struct s_queue_bf *parrent;
	struct s_queue_bf *next;
}              t_queue_bf;

t_queue_bf	*init_belmon_ford(void)
{
	t_queue_bf *belmon_ford;

	if (!(belmon_ford = malloc(sizeof(t_queue_bf) * 1)))
		terminate(ERR_ALLOCATION);
	belmon_ford->room_name = NULL;
	belmon_ford->accumulated_value = 0;
	belmon_ford->parrent = NULL;
	belmon_ford->next = NULL;
	return (belmon_ford);
}

void put_start_data(t_queue_bf *belmon_ford, t_room* start)
{
	belmon_ford->room_name = start->room_name;
}

void put_data_in_queue(t_queue_bf *tmp_queue, t_queue_bf *belmon_ford, t_node *link)
{
	tmp_queue->room_name = link->node;
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

void    add_links_to_belmon_ford_queue(t_room *tmp_room, t_queue_bf *belmon_ford)
{
	t_node *tmp_link;
	t_queue_bf *tmp_queue;
	t_queue_bf *end_queue;

	tmp_link = tmp_room->link;
	end_queue = find_end_of_queue(belmon_ford);
	while (tmp_link)
	{
		if (tmp_link->direction != UPSTREAM && (belmon_ford->parrent == NULL || ft_strcmp(tmp_link->node, belmon_ford->parrent->room_name) != 0))
		{
			tmp_queue = init_belmon_ford();
			put_data_in_queue(tmp_queue, belmon_ford, tmp_link);
			end_queue->next = tmp_queue;
			end_queue = end_queue->next;
		}
		tmp_link = tmp_link->next;
	}
}

void    algorithm_belmon_ford(t_lem_in *lem_in) {
	t_queue_bf *belmon_ford;
	t_room *tmp;

	belmon_ford = init_belmon_ford();
	put_start_data(belmon_ford, lem_in->start);
	while (ft_strcmp(belmon_ford->room_name, lem_in->end->room_name) != 0)
	{
		tmp = find_room_in_hashtable(belmon_ford->room_name,lem_in->ht_rooms);
		add_links_to_belmon_ford_queue(tmp, belmon_ford);                         // проблема что сейчас он хочет добавить 4out а это цикл - нужно чтоб он его не  добавлял
		belmon_ford = belmon_ford->next;
	}
}

void    algorithm_suurballe(t_lem_in *lem_in, int maxpath)
{
	turn_around_links(lem_in, lem_in->paths[0]);
	dub_rooms(lem_in, lem_in->paths[0]);
	algorithm_belmon_ford(lem_in);
	/*while (maxpath > lem_in)
	{
		algorithm_belmon_ford(lem_in); прошли по  минимальной стоимости до END
	    собрали по ссылкам в очереди путь от start
	    turn_around(lem_in);
		dub_rooms(); при дублирование комнаты сплит линков надо удалить
		count_pathes(); нашли пути из END
	    is_enough();
	}*/
}