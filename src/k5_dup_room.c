/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k5_dup_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:29:12 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 21:29:14 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	create_links_with_zero_price(t_room *room_in, t_room *room_out)
{
	add_link_with_zero_price(room_in->link, room_out->room_name);
	change_roomtype_to_out_duprooms(room_in);
	add_link_with_zero_price(room_out->link, room_in->room_name);
	change_roomtype_to_in_duprooms(room_out);
}

void	find_place_for_link_in_room_out(t_room *out, t_node *tmp)
{
	t_node *tmp2;

	if (out->link == NULL)
		out->link = tmp;
	else
	{
		tmp2 = out->link;
		while (tmp2->next != NULL)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
}

void	create_and_classify_links(t_room *in, t_room *out, t_hashtable *ht)
{
	t_node	*tmp;
	t_node	*tmp_next;
	int		i;

	tmp_next = NULL;
	tmp = in->link;
	i = 0;
	while (tmp)
	{
		i = 0;
		if (tmp->price == MINUS_ONE && tmp->direction == UPSTREAM)
		{
			if (tmp->next != NULL)
				tmp_next = tmp->next;
			move_link(in, out, tmp, ht);
			if (tmp_next != NULL)
				tmp = tmp_next;
			else
				break ;
		}
		if (tmp->price == MINUS_ONE && tmp->direction == DOWNSTREAM)
			change_roomtype_to_in_and_upstream_direction(in, tmp, ht);
		if (tmp->price == ONE && tmp->direction == BOTH_STREAM)
		{
			tmp->direction = UPSTREAM;
			change_roomtype_to_in_and_downstream_direction(in, tmp, ht);
			split_link_for_room_out(out, tmp, ht);
		}
		if (tmp->type_room == IN && tmp->direction == UPSTREAM)
		{
			if (tmp->next != NULL)
			{
				tmp_next = tmp->next;
				i++;
			}
			move_link(in, out, tmp, ht);
			if (tmp_next != NULL)
				tmp = tmp_next;
		}
		i == 0 ? (tmp = tmp->next) : 0;
	}
	create_links_with_zero_price(in, out);
}

void	dub_rooms(t_lem_in *lem_in, t_path *path)
{
	t_path *tmp;
	t_room *current_room;

	tmp = path->next;
	while (ft_strcmp(tmp->name, lem_in->end->room_name) != 0)
	{
		current_room = find_room_with_type_in_hashtable(tmp->name,
		tmp->typeroom, lem_in->ht_rooms);
		if (current_room->in_out == IN_OUT)
		{
			current_room->in_out = IN;
			create_room_out_and_classify_links(current_room, lem_in->ht_rooms);
		}
		tmp = tmp->next;
	}
}
