/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k2_dup_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:08:36 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 20:08:38 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_room	*create_room_out_dup(char *name)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		terminate(ERR_ROOM_INIT);
	if (!(room->room_name = ft_strdup(name)))
		terminate(ERR_ROOM_INIT);
	room->in_out = OUT;
	room->next = NULL;
	room->link = NULL;
	room->bfs_visit = UNVISITED;
	room->ek_visit = UNVISITED;
	room->bfs_level = -1;
	room->outgoing_links = NULL;
	room->incoming_links = NULL;
	room->cut = UNCUT;
	return (room);
}

t_room	*create_room_out(t_room *room)
{
	t_room *tmp;

	tmp = room;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_room_out_dup(room->room_name);
	tmp = tmp->next;
	return (tmp);
}

void	add_link_with_zero_price(t_node *link, char *toward)
{
	t_node	*tmp;

	tmp = link;
	if (tmp == NULL)
	{
		link = neighbour_init();
		if (!(link->node = ft_strdup(toward)))
			terminate(ERR_ROOM_INIT);
	}
	else
	{
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				tmp->next = neighbour_init();
				tmp = tmp->next;
				if (!(tmp->node = ft_strdup(toward)))
					terminate(ERR_ROOM_INIT);
				break ;
			}
			tmp = tmp->next;
		}
	}
	tmp->direction = BOTH_STREAM;
	tmp->price = ZERO;
}

void	move_not_first_link_of_room_in(t_room *in, t_room *out, char *link_name)
{
	t_node *tmp;
	t_node *lagged_tmp;

	lagged_tmp = in->link;
	tmp = in->link->next;
	while (ft_strcmp(tmp->node, link_name) != 0)
	{
		lagged_tmp = lagged_tmp->next;
		tmp = tmp->next;
	}
	lagged_tmp->next = tmp->next;
	tmp->next = NULL;
	find_place_for_link_in_room_out(out, tmp);
}

void	move_first_link_of_room_in(t_room *in, t_room *out)
{
	t_node *tmp;

	tmp = in->link;
	if (in->link->next != NULL)
		in->link = in->link->next;
	else
		in->link = NULL;
	tmp->next = NULL;
	find_place_for_link_in_room_out(out, tmp);
}
