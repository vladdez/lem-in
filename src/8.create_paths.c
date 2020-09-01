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
		/*if (j == 1 && len < 120)
		{
				ft_printf("%d) %s[%d] \n", len, tmp_room->room_name, tmp_room->bfs_level);
				if (tmp_room->link != NULL)
					print_links(tmp_room);
				ft_printf(" \n");
		}*/
		if (tmp_room == lem_in->end || tmp_room == NULL ||
				tmp_room->ek_visit == lem_in->ek_used)
		{
			delete_current_path(lem_in->paths[j]);
			lem_in->paths[j] = NULL;
			return (-1);
		}
		if (tmp_room != lem_in->start)
		{
			tmp_room->bfs_visit = lem_in->bfs_used;
			tmp_room->ek_visit = lem_in->ek_used;
		}
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

int		len_of_actual_paths(t_lem_in *lem_in)
{
	int		i;
	int		j;
	t_path	**p;

	i = 0;
	j = 0;
	p = lem_in->paths;
	while (p[i] != NULL)
	{
		if (p[i] && p[i]->next)
			j++;
		i++;
	}
	return (j);
}

void	check_order(t_path **paths, t_lem_in *lem_in)
{
	t_path	**curr;
	t_path	*tmp;
	int		i;
	int		j;

	i = 1;
	curr = paths;
	tmp = NULL;
	j = len_of_actual_paths(lem_in);
	if (j > 1)
	{
		while (curr[i])
		{
			if (curr[i]->len < curr[i - 1]->len)
			{
				tmp = curr[i];
				curr[i] = curr[i - 1];
				curr[i - 1] = tmp;
			}
			i++;
		}
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
		if (maxpath > i && i < 2)
			second_plan(lem_in, maxpath);
		check_order(lem_in->paths, lem_in);
	}
	return (cut_s);
}
