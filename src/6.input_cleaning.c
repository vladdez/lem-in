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

#include "lem-in.h"

void	clean_and_free_link(t_node *kill)
{
	free(kill->node);
	kill->node = NULL;
	kill->next = NULL;
}

t_node	*delete_this_link(t_room *room, char *name_of_link_to_delete)
{
	t_node	*tmp_link;
	t_node	*tmp_lagging_link;

	tmp_link = room->link;
	if (ft_strcmp(tmp_link->node, name_of_link_to_delete) == 0)
	{
		if (tmp_link->next == NULL)
			clean_and_free_link(room->link);
		else
		{
			room->link = tmp_link->next;
			clean_and_free_link(tmp_link);
			free(tmp_link);
		}
		return (room->link);
	}
	else
	{
		tmp_lagging_link = tmp_link;
		tmp_link = tmp_link->next;
		while (tmp_link)
		{
			if (ft_strcmp(tmp_link->node, name_of_link_to_delete) == 0)
			{
				tmp_lagging_link->next = tmp_link->next;
				clean_and_free_link(tmp_link);
				return (tmp_lagging_link->next);
			}
			else
			{
				tmp_lagging_link = tmp_lagging_link->next;
				tmp_link = tmp_link->next;
			}
		}
	}
}

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

void	imput_cleaning(t_lem_in *lem_in)
{
	delete_outgoing_links_for_end(lem_in->end, lem_in->ht_rooms);
	lem_in->end->bfs_level = INT_MAX;
}
