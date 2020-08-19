/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.create_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:40:02 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/17 18:52:14 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_path	*create_one_path(t_room *cur)
{
	t_path *pa;

	if (!(pa = (t_path *)ft_memalloc(sizeof(t_path))))
		terminate(ERR_PATH_INIT);
	pa->name = ft_strdup(cur->room_name);
	pa->len = -1;
	pa->ant_index = 0;
	pa->head = 0;
	return (pa);
}

t_room	*find_lowest_bfs(t_node *n, t_hashtable *ht_rooms)
{
	t_node	*cur;
	t_room	*tmp_room;
	t_room	*lowest_bfs_room;
	int		lowest;
	int		level;

	lowest = 2147483647;
	cur = n;
	lowest_bfs_room = NULL;
	while (cur)
	{
		tmp_room = FindRoomInHashtable(cur->node, ht_rooms);
		if (tmp_room->visit2 == UNVISITED)
		{
			level = tmp_room->bfs_level;
			if (level < lowest)
			{
				lowest = level;
				lowest_bfs_room = tmp_room;
			}
		}
		cur = cur->next;
	}
	return (lowest_bfs_room);
}

t_room	*find_best_room(t_room *cur, t_hashtable *ht_rooms)
{
	t_room *tmp;

	if ((len_nei(cur->link) == 1))
		return (FindRoomInHashtable(cur->link->node, ht_rooms));// если один сосед то сразу ее, в текущем коде сюда не заходит
	else
		tmp = find_lowest_bfs(cur->link, ht_rooms); // иначе по наименьшему bfs
	return (tmp);
}

void	create_way(t_lem_in *lem_in, int cut, int j)
{
	t_room	*cur;
	t_path	*tmp;
	int		len;
	t_room	*tmp_room;

	tmp = NULL;
	while (j < cut)
	{
		len = 0;
		cur = lem_in->end;
		lem_in->paths[j] = create_one_path(lem_in->end);  // инизализация, важно что первый  это END
		while (cur != lem_in->start)                      // засись команты в путь по связному списку
		{
			tmp_room = find_best_room(cur, lem_in->ht_rooms);
			if (tmp_room == lem_in->end || tmp_room == NULL)
			{
				delete_current_path(lem_in->paths[j]);
				lem_in->paths[j] = NULL;
				break;
			}
			if (tmp_room != lem_in->start)
				tmp_room->visit2 = VISITED;
			cur = tmp_room;
			tmp = create_one_path(cur); // указатель где начинается путь
			tmp->next = lem_in->paths[j];
			lem_in->paths[j] = tmp;
			len++;
			tmp = NULL;
		}
		if (lem_in->paths[j])
			lem_in->paths[j]->len = len; // !!! здесь потенциальная ошибка так как можем пропустить путь, они не записываются друг за другом
		j++;
	}
}

int		create_paths(t_lem_in *lem_in)
{
	int		cut_s;
	int		cut_e;
	int		maxpath;
	int		i;

	i = 0;
	cut_s = is_short_circuit(lem_in);
	if (cut_s != 0)
	{
		cut_e = len_nei(lem_in->end->link);
		maxpath = cut_e > cut_s ? cut_s : cut_e;
		lem_in->paths = (t_path **)malloc(sizeof(t_path *) * (maxpath + 1));
		while (i < maxpath + 1)
			lem_in->paths[i++] = NULL;
		lem_in->path_num = maxpath;
		create_way(lem_in, maxpath, 0);
	}
	return (cut_s);  // мы это отправлает по делу чтобы отследить короткое замыкание
}
