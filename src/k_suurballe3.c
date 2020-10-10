/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_suurballe3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:50:31 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 21:50:33 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	clean_all_edmon_karts_marks2(t_lem_in *lem_in,
t_path *tmp, t_room *tmp_room)
{
	while (tmp)
	{
		tmp_room = find_room_with_type_in_hashtable(tmp->name,
		tmp->typeroom, lem_in->ht_rooms);
		if (tmp_room != NULL)
			tmp_room->ek_visit = UNVISITED;
		else
		{
			tmp_room = find_room_with_type_in_hashtable(tmp->name,
			IN, lem_in->ht_rooms);
			tmp_room->ek_visit = UNVISITED;
			tmp_room = find_room_with_type_in_hashtable(tmp->name,
			OUT, lem_in->ht_rooms);
			tmp_room->ek_visit = UNVISITED;
		}
		tmp = tmp->next;
	}
}

void	clean_all_edmon_karts_marks(t_lem_in *lem_in)
{
	t_path	*tmp;
	t_room	*tmp_room;
	int		i;

	i = 0;
	tmp_room = NULL;
	while (i <= lem_in->path_num)
	{
		if (lem_in->paths[i] != NULL)
		{
			tmp = lem_in->paths[i];
			clean_all_edmon_karts_marks2(lem_in, tmp, tmp_room);
		}
		i++;
	}
}

t_room	*find_best_link_with_price2(t_node *dub_link,
t_room *dub_room, t_hashtable *ht)
{
	if (dub_link != NULL)
	{
		dub_room = find_room_with_type_in_hashtable(dub_link->node,
		dub_link->type_room, ht);
		if (dub_room != NULL)
		{
			if (dub_room->ek_visit == UNVISITED)
				dub_room->ek_visit = VISITED;
			else
				return (NULL);
			return (find_best_link_with_price(dub_room->link, ht));
		}
		else
			return (NULL);
	}
	else
		return (NULL);
}

t_room	*find_best_link_with_price(t_node *cur, t_hashtable *ht)
{
	t_node	*dub_link;
	t_room	*dub_room;
	t_room	*room;

	dub_link = NULL;
	dub_room = NULL;
	while (cur)
	{
		if (cur->direction == DOWNSTREAM && cur->price == MINUS_ONE)
		{
			room = find_room_with_type_in_hashtable(cur->node,
			cur->type_room, ht);
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
	return (find_best_link_with_price2(dub_link, dub_room, ht));
}
