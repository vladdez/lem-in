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

t_room		*find_lowest_bfs3(t_node *n, t_hashtable *ht_rooms, t_lem_in *lem_in)
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
		if (tmp_room->visit4 != VISITED && tmp_room != lem_in->mem)
		{
			//printf("? %s %d   ", tmp_room->room_name, tmp_room->bfs_level2);
			level = tmp_room->bfs_level2;
			if (level < lowest && level != -1)
			{
				lowest = level;
				lowest_bfs_room = tmp_room;
			}
		}
		cur = cur->next;
	}
	//printf("\nwinner %s %d   \n", lowest_bfs_room->room_name, lowest_bfs_room->bfs_level2);
	return (lowest_bfs_room);
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
		//printf("j %d\n", j);
	}
}
