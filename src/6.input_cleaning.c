/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_unused_rooms.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 12:28:36 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/19 19:23:51 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void    clean_and_free_link(t_node *kill)
{
	free(kill->node);
	kill->node = NULL;
	kill->next = NULL;
}


t_node  *DeleteThisLink(t_room *room, char *nameOfLinkToDelete)
{
	t_node  *tmpLink;
	t_node  *tmpLaggingLink;

	tmpLink = room->link;
	if (ft_strcmp(tmpLink->node, nameOfLinkToDelete) == 0)
	{
		if (tmpLink->next == NULL)
			clean_and_free_link(room->link);
		else
		{
			room->link = tmpLink->next;
			clean_and_free_link(tmpLink);
			free(tmpLink);
		}
		return (room->link);
	}
	else
	{
		tmpLaggingLink = tmpLink;
		tmpLink = tmpLink->next;
		while(tmpLink)
		{
			if (ft_strcmp(tmpLink->node, nameOfLinkToDelete) == 0)
			{
				tmpLaggingLink->next = tmpLink->next;
				clean_and_free_link(tmpLink);
				return (tmpLaggingLink->next);
			}
			else
			{
				tmpLaggingLink = tmpLaggingLink->next;
				tmpLink = tmpLink->next;
			}
		}
	}
}

void    deleteOutgoingLinksforEnd(t_room *EndRoom, t_hashtable *ht_rooms)
{
	t_node  *tmpLinkOfEndRoom;
	t_room  *tmpRoom;

	tmpLinkOfEndRoom = EndRoom->link;
	while ( tmpLinkOfEndRoom != NULL && tmpLinkOfEndRoom->node != NULL)
	{
		tmpRoom = FindRoomInHashtable(tmpLinkOfEndRoom->node, ht_rooms);
		if (tmpRoom->bfs_level == -1)
		{
			tmpLinkOfEndRoom = DeleteThisLink(EndRoom,tmpLinkOfEndRoom->node);
			DeleteThisLink(tmpRoom, EndRoom->room_name);
			if (tmpRoom->link->node != NULL)
				deleteOutgoingLinksforEnd(tmpRoom,ht_rooms);
		}
		else
			tmpLinkOfEndRoom = tmpLinkOfEndRoom->next;
	}
}

void    ImputCleaning(t_lem_in *lem_in)
{
	deleteOutgoingLinksforEnd(lem_in->end, lem_in->ht_rooms);
	lem_in->end->bfs_level = INT_MAX;
}
