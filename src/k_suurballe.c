//
// Created by Ирина Деева on 07.09.2020.
//

#include "../inc/lem_in.h"

void    clean_all_edmon_karts_marks(t_lem_in *lem_in)
{
	t_path *tmp;
	t_room *tmp_room;
	int     i;

	i = 0;
	while (i <= lem_in->path_num)
	{
		if (lem_in->paths[i] != NULL)
		{
			tmp = lem_in->paths[i];
			while (tmp)
			{

				tmp_room = find_room_with_type_in_hashtable(tmp->name, tmp->typeroom, lem_in->ht_rooms);
				if (tmp_room != NULL)
				{
					tmp_room->ek_visit = UNVISITED;
					tmp = tmp->next;
				}
				else
					{
					tmp_room = find_room_with_type_in_hashtable(tmp->name, IN, lem_in->ht_rooms);
					tmp_room->ek_visit = UNVISITED;
					tmp_room = tmp_room->next;
					tmp_room->ek_visit = UNVISITED;
					tmp = tmp->next;
				}
			}
		}
		i++;
	}
}

void	clean_all_current_pathes(t_path **pa, int path_num)
{
	int		i;
	t_path	*kill;

	i = 0;
	while (i <= path_num)
	{
		if (pa[i] != NULL)
		{
			while (pa[i])
			{
				kill = pa[i];
				pa[i] = pa[i]->next;
				free(kill->name);
				free(kill);
			}
		}
		i++;
	}
}

t_room	*find_best_link_with_price(t_node *cur, t_hashtable *ht)
{
	t_node *dub_link;
	t_room *dub_room;
	t_room *room;

	while (cur)
	{
		if (cur->direction == DOWNSTREAM && cur->price == MINUS_ONE)
		{
			room = find_room_with_type_in_hashtable(cur->node, cur->type_room, ht);
			if (room->ek_visit == UNVISITED)
			{
				room->ek_visit = VISITED;
				return (room);
			}
		}
		if (cur->price == ZERO)
			dub_link = cur;
		cur = cur->next;
	}
		dub_room = find_room_with_type_in_hashtable(dub_link->node, dub_link->type_room, ht);
		if (dub_room != NULL) {
			dub_room->ek_visit = VISITED;
			return (find_best_link_with_price(dub_room->link, ht));
		}
		else
			return (NULL);
}

int		create_way_sub_with_price(t_lem_in *lem_in, t_path *tmp, t_room *cur, int j)
{
	t_room	*tmp_room;
	int		len;

	len = 0;
	while (cur != lem_in->start)
	{
		tmp_room = find_best_link_with_price(cur->link, lem_in->ht_rooms);
		if (tmp_room == lem_in->end || tmp_room == NULL)
		{
			delete_current_path(lem_in->paths[j]);
			lem_in->paths[j] = NULL;
			return (-1);
		}
		cur = tmp_room;
		tmp = create_one_path(cur);
		tmp->next = lem_in->paths[j];
		lem_in->paths[j] = tmp;
		tmp = NULL;
		len++;
	}
	lem_in->start->ek_visit = UNVISITED;
	return (len);
}

void	create_way_with_price(t_lem_in *lem_in, int *maxpath)
{
	t_room	*tmp_room;
	t_path	*tmp_path;
	int		len;
	int     i;
	int     max;

	tmp_path = NULL;
	len = 0;
	i = 0;
	max = *maxpath;
	while (i < max)
	{
		tmp_room = lem_in->end;
		lem_in->paths[i] = create_one_path(lem_in->end);
		len = create_way_sub_with_price(lem_in, tmp_path, tmp_room, i);
		if (lem_in->paths[i])
		{
			lem_in->paths[i]->len = len;
			i++;
			lem_in->path_num++;
		}
		else if (len == -1)
			max--;
	}
}

void    edmon_karts_by_link_price(t_lem_in *lem_in, int *maxpath)
{
	create_way_with_price(lem_in, maxpath);
}

void    count_pathes(t_lem_in *lem_in, int *maxpath)
{
	//clean_all_edmon_karts_marks(lem_in); // очистить все метки
	clean_all_current_pathes(lem_in->paths, lem_in->path_num);
	lem_in->path_num = 0;
	edmon_karts_by_link_price(lem_in, maxpath);
}

void    algorithm_suurballe(t_lem_in *lem_in, int *maxpath)
{
	t_queue_bf *belmon_ford;
	t_path *tmp_path;

	clean_all_edmon_karts_marks(lem_in);
	tmp_path = lem_in->paths[0];
	turn_around_links(lem_in, tmp_path );  // поворот по самому короткому 1ому пути
	dub_rooms(lem_in, tmp_path);          // дубль по самому короткому 1ому пути
	while (*maxpath > lem_in->path_num)
	{
		belmon_ford = algorithm_belmon_ford(lem_in); // поиск нового пути
		tmp_path = put_belmon_ford_to_the_path(lem_in, belmon_ford); // перенос его в структуру path
		turn_around_links(lem_in, tmp_path); // поворот нового пути
		dub_rooms(lem_in, tmp_path); // дублирование нового пути
		count_pathes(lem_in, maxpath); // нашли пути из END
		if (is_enough(lem_in) == 1)
			break;
		clean_all_edmon_karts_marks(lem_in);
		//free_queue_belmon_ford(belmon_ford);   // free the bf_queue
	}

	// maxpath or is_enough();
	/*while (maxpath > lem_in)
	{
		algorithm_belmon_ford(lem_in); прошли по  минимальной стоимости до END
	    собрали по ссылкам в очереди путь от start
	    turn_around(lem_in);
		dub_rooms(); при дублирование комнаты сплит линков надо удалить
		count_pathes(); нашли пути из END

	}*/
}