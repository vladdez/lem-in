/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_unused_rooms.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 12:28:36 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/20 17:27:19 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	delete_outgoing_links_for_end(t_room *end_room, t_hashtable *ht_rooms)
{
	t_node	*end_room_link;
	t_room	*tmp_room;

	end_room_link = end_room->link;
	while (end_room_link != NULL && end_room_link->node != NULL)
	{
		tmp_room = find_room_in_hashtable(end_room_link->node, ht_rooms);
		if (tmp_room->bfs_level == -1)
		{
			end_room_link = delete_this_link(end_room, end_room_link->node);
			delete_this_link(tmp_room, end_room->room_name);
			if (tmp_room->link->node != NULL)
				delete_outgoing_links_for_end(tmp_room, ht_rooms);
		}
		else
			end_room_link = end_room_link->next;
	}
}

void	input_cleaning(t_lem_in *lem_in)
{
	delete_outgoing_links_for_end(lem_in->end, lem_in->ht_rooms);
	lem_in->end->bfs_level = INT_MAX;
}
