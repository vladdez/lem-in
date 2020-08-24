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

#include "lem-in.h"

int		is_enough(t_lem_in *lem_in)
{
	int		p;
	int		totallen;
	int		path_num_fl;

	path_num_fl = lem_in->path_num - 1;
	p = 0;
	totallen = 0;
	while (p != path_num_fl)
	{
		if (lem_in->paths[p])
			totallen += lem_in->paths[p]->len;
		p++;
	}
	ft_printf("totallen %d lem_in->ant_num %d\n", totallen, lem_in->ant_num);
	if (lem_in->ant_num > totallen)
		return (0);
	else
		return (1);
	return (0);
}

void	get_mem(t_lem_in *lem_in)
{
	t_path	*pa;

	pa = lem_in->paths[0];
	while (pa->next->next)
		pa = pa->next;
	lem_in->mem = find_room_in_hashtable(pa->name, lem_in->ht_rooms);
}

t_room		*find_lowest_bfs2(t_node *n, t_hashtable *ht_rooms, t_lem_in *lem_in)
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
		if (tmp_room->visit3 != VISITED && tmp_room != lem_in->mem)
		{
			level = tmp_room->bfs_level;
			if (level < lowest)
			{
				lowest = level;
				lowest_bfs_room = tmp_room;
			}
		}
		else if (tmp_room == lem_in->mem)
			lem_in->mem = NULL;
		/*else if (tmp_room->visit3 == VISITED)
			ft_printf("%s room_name visited \n", tmp_room->room_name);*/
		cur = cur->next;
	}
	return (lowest_bfs_room);
}

t_room		*find_best_room2(t_room *cur, t_hashtable *ht_rooms, t_lem_in *lem_in)
{
	t_room *tmp;

	tmp = NULL;
	if ((len_nei(cur->link) == 1))
		return (tmp = find_room_in_hashtable(cur->link->node, ht_rooms));
	else
	{
		if (lem_in->bfs_type == 0)
			tmp = find_lowest_bfs2(cur->incoming_links, ht_rooms, lem_in);
		else if (lem_in->bfs_type == 1)
		{
			tmp = find_lowest_bfs3(cur->link, ht_rooms, lem_in);
			//printf("lowest_bfs_room %s %d\n", tmp->room_name, tmp->bfs_level);
		}
	}
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
		//if (tmp_room != NULL)
		//	printf("%s room_name, out %d, in %d \n", tmp_room->room_name, len_nei(tmp_room->outgoing_links), len_nei(tmp_room->incoming_links));
		if (tmp_room == lem_in->end || tmp_room == NULL ||
		tmp_room->visit4 == 1)
		{
			delete_current_path(lem_in->paths[j]);
			lem_in->paths[j] = NULL;
			return (-1);
		}
		if (tmp_room != lem_in->start)
		{
			tmp_room->visit3 = VISITED;
			tmp_room->visit4 = VISITED;
		}
		cur = tmp_room;
		tmp = create_one_path(cur);
		tmp->next = lem_in->paths[j];
		lem_in->paths[j] = tmp;
		tmp = NULL;
		len++;
	}
	printf("\n");
	return (len);
}

void		create_way2(t_lem_in *lem_in, int j)
{
	t_room	*cur;
	t_path	*tmp;
	int		len;

	tmp = NULL;
	cur = lem_in->end;
	lem_in->paths[j] = create_one_path(lem_in->end);
	len = create_way_sub2(lem_in, tmp, cur, j);
	if (lem_in->paths[j])
		lem_in->paths[j]->len = len;
}

void	second_plan(t_lem_in *lem_in, int maxpath)
{
	int			i;
	t_queue		*q;

	i = is_enough(lem_in);
	if (i != 1)
	{
		get_mem(lem_in);
		ft_printf("NOT ENOUGH - %s\n", lem_in->mem->room_name);
		free_paths(lem_in->paths, lem_in->path_num);
		lem_in->paths = (t_path **)malloc(sizeof(t_path *) * (maxpath + 2));
		while (i <= (maxpath + 1))
			lem_in->paths[i++] = NULL;
		create_way2(lem_in, 0);
		q = bfs2(lem_in);
		lem_in->bfs_type = 1;
		create_way3(lem_in, maxpath, 1);
		lem_in->path_num = len_of_actual_paths(lem_in, maxpath);
		free(q);
	}
	else
		ft_printf("ENOUGH\n");
}
