/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10.suurb_flow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 16:03:29 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/18 16:03:43 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_room		*find_lowest_bfs2(t_node *n, t_hashtable *ht_rooms,
t_lem_in *lem_in, int lowest)
{
	t_node	*cur;
	t_room	*tmp_room;
	t_room	*lowest_bfs_room;
	int		level;

	cur = n;
	lowest_bfs_room = NULL;
	while (cur)
	{
		tmp_room = find_room_in_hashtable(cur->node, ht_rooms);
		if (tmp_room->bfs_visit == lem_in->bfs_used && tmp_room->ek_visit != 2)
		{
			if (are_nei_valid(tmp_room, lem_in) > 0)
			{
				level = tmp_room->bfs_level;
				if (level < lowest && level >= 0)
				{
					lowest = level;
					lowest_bfs_room = tmp_room;
				}
			}
		}
		cur = cur->next;
	}
	return (lowest_bfs_room);
}

t_room		*find_best_room2(t_room *cur,
t_hashtable *ht_rooms, t_lem_in *lem_in)
{
	t_room *tmp;

	tmp = NULL;
	if ((len_nei(cur->link) == 1))
		return (tmp = find_room_in_hashtable(cur->link->node, ht_rooms));
	else
		tmp = find_lowest_bfs2(cur->link, ht_rooms, lem_in, 2147483647);
	return (tmp);
}

int			create_way_sub2(t_lem_in *lem_in, t_path *tmp, t_room *cur, int j)
{
	t_room	*tmp_room;
	int		len;

	len = 0;
	while (cur != lem_in->start)
	{
		tmp_room = find_best_room2(cur, lem_in->ht_rooms, lem_in);
		if (tmp_room == lem_in->end || tmp_room == NULL ||
		tmp_room->ek_visit == 2)
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

void		create_way3(t_lem_in *lem_in, int cut, int j)
{
	t_room	*cur;
	t_path	*tmp;
	int		len;

	tmp = NULL;
	len = 0;
	while (j <= cut)
	{
		cur = lem_in->end;
		lem_in->paths[j] = create_one_path(lem_in->end);
		len = create_way_sub2(lem_in, tmp, cur, j);
		if (lem_in->paths[j])
		{
			lem_in->paths[j]->len = len;
			j++;
		}
		else if (len == -1 && lem_in->paths[j++])
			cut--;
		if (j == 1)
			get_mem(lem_in, 2);
		else if (j > 1)
			is_cutted(lem_in);
		bfs(lem_in);
	}
}

void		second_plan(t_lem_in *lem_in, int maxpath)
{
	int			i;

	i = is_enough(lem_in);
	if (i != 1)
	{
		lem_in->ek_used++;
		get_mem(lem_in, 1);
		free_paths(lem_in->paths, lem_in->path_num);
		lem_in->paths = (t_path **)malloc(sizeof(t_path *) * (maxpath + 2));
		while (i <= (maxpath + 1))
			lem_in->paths[i++] = NULL;
		bfs(lem_in);
		create_way3(lem_in, maxpath, 0);
		lem_in->path_num = len_of_actual_paths(lem_in);
	}
}
