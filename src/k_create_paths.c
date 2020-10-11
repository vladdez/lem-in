/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.create_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:40:02 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/24 20:56:55 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_path	*create_one_path(t_room *cur)
{
	t_path *pa;

	if (!(pa = (t_path *)ft_memalloc(sizeof(t_path))))
		terminate(ERR_PATH_INIT);
	pa->name = ft_strdup(cur->room_name);
	pa->typeroom = IN_OUT;
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
		tmp_room = find_room_in_hashtable(cur->node, ht_rooms);
		if (tmp_room->ek_visit != VISITED)
		{
			level = tmp_room->bfs_level;
			if (level < lowest && level >= 0)
			{
				lowest = level;
				lowest_bfs_room = tmp_room;
			}
		}
		cur = cur->next;
	}
	return (lowest_bfs_room);
}

int		create_way_sub(t_lem_in *lem_in, t_path *tmp, t_room *cur, int j)
{
	t_room	*tmp_room;
	int		len;

	len = 0;
	while (cur != lem_in->start)
	{
		tmp_room = find_best_room(cur, lem_in->ht_rooms);
		if (tmp_room == lem_in->end || tmp_room == NULL ||
				tmp_room->ek_visit == lem_in->ek_used)
		{
			delete_current_path(lem_in->paths[j]);
			lem_in->paths[j] = NULL;
			return (-1);
		}
		if (tmp_room != lem_in->start)
			upd_visits(lem_in, tmp_room);
		cur = tmp_room;
		tmp = create_one_path(cur);
		tmp->next = lem_in->paths[j];
		lem_in->paths[j] = tmp;
		tmp = NULL;
		len++;
	}
	return (len);
}

void	create_way(t_lem_in *lem_in, int cut, int j)
{
	t_room	*cur;
	t_path	*tmp;
	int		len;

	tmp = NULL;
	len = 0;
	while (j < cut)
	{
		cur = lem_in->end;
		lem_in->paths[j] = create_one_path(lem_in->end);
		len = create_way_sub(lem_in, tmp, cur, j);
		if (lem_in->paths[j])
		{
			lem_in->paths[j]->len = len;
			bfs(lem_in);
			j++;
		}
		else if (len == -1)
			cut--;
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
		cut_e = len_nei(lem_in->end->incoming_links);
		maxpath = cut_e > cut_s ? cut_s : cut_e;
		lem_in->paths = (t_path **)malloc(sizeof(t_path *) * (maxpath + 1));
		while (i < maxpath + 1)
			lem_in->paths[i++] = NULL;
		create_way(lem_in, maxpath, 0);
		i = len_of_actual_paths(lem_in);
		lem_in->path_num = i;
		check_order(lem_in->paths, lem_in, 1, 0);
		if (maxpath > i)
		{
			second_plan(lem_in, maxpath);
			check_order(lem_in->paths, lem_in, 1, 0);
		}
	}
	return (cut_s);
}
