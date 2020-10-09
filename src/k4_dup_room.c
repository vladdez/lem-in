/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k4_dup_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:27:43 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 21:27:45 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	move_link_to_room_out(t_room *in, t_room *out, char *link_name)
{
	if (ft_strcmp(in->link->node, link_name) == 0)
		move_first_link_of_room_in(in, out);
	else
		move_not_first_link_of_room_in(in, out, link_name);
}

void	move_link(t_room *in, t_room *out, t_node *link, t_hashtable *ht)
{
	move_link_to_room_out(in, out, link->node);
	change_roomtype_to_out(out, link, ht);
}

/*
** найти линк у самой команты (она по дефолту in)  и перенести в аут
** найти в команту по имени линка и обзначить связь что она входит в аут
*/

void	create_link_dup(t_room *out, t_node *link_to_copy, t_hashtable *ht)
{
	t_room	*tmp_room;
	t_node	*tmp_link;

	tmp_room = find_room_with_type_in_hashtable(link_to_copy->node,
	link_to_copy->type_room, ht);
	tmp_link = tmp_room->link;
	while (tmp_link->next != NULL)
		tmp_link = tmp_link->next;
	tmp_link->next = neighbour_init();
	tmp_link = tmp_link->next;
	tmp_link->type_room = OUT;
	if (!(tmp_link->node = ft_strdup(out->room_name)))
		terminate(ERR_ALLOCATION);
	tmp_link->price = link_to_copy->price;
	tmp_link->direction = UPSTREAM;
}

void	split_link_for_room_out(t_room *out, t_node *link_to_copy,
t_hashtable *ht)
{
	t_node *tmp;

	if (out->link == NULL)
	{
		out->link = neighbour_init();
		tmp = out->link;
	}
	else
	{
		tmp = out->link;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = neighbour_init();
		tmp = tmp->next;
	}
	if (!(tmp->node = ft_strdup(link_to_copy->node)))
		terminate(ERR_ROOM_INIT);
	tmp->price = link_to_copy->price;
	tmp->direction = DOWNSTREAM;
	tmp->type_room = link_to_copy->type_room;
	create_link_dup(out, tmp, ht);
}

void	create_room_out_and_classify_links(t_room *room_in, t_hashtable *ht)
{
	t_room *room_out;

	room_out = create_room_out(room_in);
	create_and_classify_links(room_in, room_out, ht);
}
