/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.find_links_direction.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 17:01:02 by bhugo             #+#    #+#             */
/*   Updated: 2020/08/21 11:17:10 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	add_node(t_node *link, char *room_name)
{
	t_node	*tmp;

	if (link->node == NULL)
	{
		link->node = room_name;
		link->next = NULL;
	}
	else
	{
		tmp = link;
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				tmp->next = neighbour_init();
				tmp = tmp->next;
				tmp->node = room_name;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

int		compare_bfs_level(t_room *current_room, t_hashtable *ht_rooms)
{
	t_node	*current_room_links;
	t_room	*room_found;
	int		deadlock;

	deadlock = 0;
	current_room_links = current_room->link;
	while (current_room_links)
	{
		room_found = find_room_in_hashtable(current_room_links->node, ht_rooms);
		if (current_room->bfs_level > room_found->bfs_level)
			add_node(current_room->incoming_links, room_found->room_name);
		else
		{
			add_node(current_room->outgoing_links, room_found->room_name);
			deadlock++;
		}
		current_room_links = current_room_links->next;
	}
	return (deadlock);
}

void	handle_links(t_room *room, t_hashtable *ht, t_node *deadlock)
{
	int	i_deadlock;

	i_deadlock = 0;
	if (room->link != NULL && room->bfs_level != -1)
	{
		i_deadlock = compare_bfs_level(room, ht);
		if (i_deadlock == 0 && room->bfs_level != INT_MAX)
			add_node(deadlock, room->room_name);
	}
}

void	find_link_direction(t_hashtable *ht_rooms)
{
	int		i;
	t_room	*current_room;
	t_node	*deadlock_name;

	i = 0;
	deadlock_name = neighbour_init();
	while (i < TABLE_SIZE)
	{
		if (ht_rooms->room[i] != NULL)
		{
			current_room = ht_rooms->room[i];
			while (current_room)
			{
				handle_links(current_room, ht_rooms, deadlock_name);
				current_room = current_room->next;
			}
		}
		i++;
	}
	free_links(deadlock_name);
}
