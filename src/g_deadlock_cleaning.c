/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.2.deadlock_cleaning.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 17:31:42 by bhugo             #+#    #+#             */
/*   Updated: 2020/08/21 11:59:47 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	print_deadlock(t_node *deadlock_room)
{
	t_node	*tmp;

	tmp = deadlock_room;
	ft_printf("deadlocks room name\n");
	while (tmp)
	{
		ft_printf("%s\n", tmp->node);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	detele_to_fork(char *links, char *deadlock, t_hashtable *ht)
{
	t_room	*deadlock_neighbour;

	deadlock_neighbour = find_room_in_hashtable(links, ht);
	delete_outgoinglink(deadlock_neighbour, deadlock);
	if (deadlock_neighbour->outgoing_links->node == NULL)
		find_links_to_deadlock(deadlock_neighbour->room_name, ht);
}

void	find_links_to_deadlock(char *deadlock_name, t_hashtable *ht_rooms)
{
	t_room	*deadlock_room;
	t_node	*incominglinks_deadlock;

	deadlock_room = find_room_in_hashtable(deadlock_name, ht_rooms);
	incominglinks_deadlock = deadlock_room->incoming_links;
	while (incominglinks_deadlock != NULL &&
			incominglinks_deadlock->node != NULL)
	{
		detele_to_fork(incominglinks_deadlock->node, deadlock_name, ht_rooms);
		delete_incominglink(deadlock_room, incominglinks_deadlock->node);
		incominglinks_deadlock = incominglinks_deadlock->next;
	}
	deadlock_room->bfs_level = -1;
}

void	clean_deadlock(t_node *deadlock_room_name, t_hashtable *ht_rooms)
{
	t_node	*current_deadlock_name;

	print_deadlock(deadlock_room_name);
	current_deadlock_name = deadlock_room_name;
	while (current_deadlock_name && current_deadlock_name->node != NULL)
	{
		find_links_to_deadlock(current_deadlock_name->node, ht_rooms);
		current_deadlock_name = current_deadlock_name->next;
	}
}
