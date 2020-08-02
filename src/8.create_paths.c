/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8.create_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:40:02 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/31 14:30:37 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		is_short_circuit(t_lem_in *lem_in)
{
	t_node	*cur;
	int		p;

	p = 0;
	cur = lem_in->start->link;
	while (cur)
	{
		if (!ft_strcmp(cur->node, lem_in->end->room_name))
		{
			ft_printf("\nL%s-%s \n", lem_in->start->room_name, lem_in->end->room_name);
			return (0);
		}
		else
			cur = cur->next;
		p++;
	}
	return (p);
}

int		len_nei(t_node *n)
{
	int		len;
	t_node	*curr;

	len = 0;
	curr = n;
	while (curr)
	{
		len++;
		curr = curr->next;
	}
	return (len);
}

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

int		find_lowest_bfs(t_node *n, t_hashtable *ht_rooms)
{
	t_node	*cur;
	int		lowest;
	int		i;
	int		tmp;
	int		r;

	lowest = 2147483647;
	cur = n;
	r = 0;
	i = 0;
	while (cur)
	{
		
		i = sum_ascii(cur->node) % TABLE_SIZE;
		if (ht_rooms->room[i]->visit2 != VISITED)
		{
			tmp = ht_rooms->room[i]->bfs_level;
			if (tmp != -1 && tmp < lowest)
			{
				lowest = tmp;
				r = i;
			}
		}
		cur = cur->next;
	}
	return (r);
}


int		find_best_room(t_room *cur, t_hashtable *ht_rooms)
{
	int i;

	i = 0;
	if ((len_nei(cur->link) == 1))
		i = sum_ascii(cur->link->node) % TABLE_SIZE;
	else
		i = find_lowest_bfs(cur->link, ht_rooms);
	return (i);
}


void	create_way(t_lem_in *lem_in, int cut, int i, int j)
{
	t_room	*cur;
	t_path	*tmp;
	int		len;

	tmp = NULL;
	while (j <= cut)
	{
		len = 0;
		cur = lem_in->end;
		lem_in->paths[j] = create_one_path(lem_in->end);
		while (cur != lem_in->start)
		{
			i = find_best_room(cur, lem_in->ht_rooms);
			if (lem_in->ht_rooms->room[i] != lem_in->start &&
			lem_in->ht_rooms->room[i] != lem_in->end)
				lem_in->ht_rooms->room[i]->visit2 = VISITED;
			cur = lem_in->ht_rooms->room[i];
			tmp = create_one_path(cur);
			tmp->next = lem_in->paths[j];
			lem_in->paths[j] = tmp;
			len++;
			tmp = NULL;
		}
		lem_in->paths[j++]->len = len;
	}
}

int		create_paths(t_lem_in *lem_in)
{
	int		cut_s;
	int		cut_e;
	int		cut;
	int		i;
	t_room	*cur;

	i = 0;
	cur = lem_in->start;
	cut_s = is_short_circuit(lem_in);
	if (cut_s != 0)
	{
		cut_e = len_nei(lem_in->end->link);
		cut = cut_e > cut_s ? cut_s : cut_e;
		lem_in->paths = (t_path **)malloc(sizeof(t_path *) * (cut + 1));
		while (i < (cut))
			lem_in->paths[i++] = NULL;
		lem_in->path_num = cut;
		create_way(lem_in, cut, 0, 1);
	}
	printf("%d - cut\n", cut_s);
	return (cut_s);
}
