/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k3_dup_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:26:31 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 21:26:35 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	change_roomtype_to_in_and_upstream_direction(t_room *in,
t_node *link, t_hashtable *ht)
{
	t_room *tmp;
	t_node *tmp_link;

	tmp = find_room_with_type_in_hashtable(link->node, link->type_room, ht);
	tmp_link = tmp->link;
	while (ft_strcmp(tmp_link->node, in->room_name) != 0)
		tmp_link = tmp_link->next;
	tmp_link->type_room = IN;
	tmp_link->direction = UPSTREAM;
}

void	change_roomtype_to_in_and_downstream_direction(t_room *in,
t_node *link, t_hashtable *ht)
{
	t_room *tmp;
	t_node *tmp_link;

	tmp = find_room_with_type_in_hashtable(link->node, link->type_room, ht);
	tmp_link = tmp->link;
	while (ft_strcmp(tmp_link->node, in->room_name) != 0)
		tmp_link = tmp_link->next;
	tmp_link->type_room = IN;
	tmp_link->direction = DOWNSTREAM;
}

void	change_roomtype_to_out(t_room *out, t_node *link, t_hashtable *ht)
{
	t_room *tmp;
	t_node *tmp_link;

	tmp = find_room_with_type_in_hashtable(link->node, link->type_room, ht);
	tmp_link = tmp->link;
	while (ft_strcmp(tmp_link->node, out->room_name) != 0)
		tmp_link = tmp_link->next;
	tmp_link->type_room = OUT;
}

void	change_roomtype_to_in_duprooms(t_room *out)
{
	t_node *tmp_link;

	tmp_link = out->link;
	while (ft_strcmp(tmp_link->node, out->room_name) != 0)
		tmp_link = tmp_link->next;
	tmp_link->type_room = IN;
}

void	change_roomtype_to_out_duprooms(t_room *in)
{
	t_node *tmp_link;

	tmp_link = in->link;
	while (ft_strcmp(tmp_link->node, in->room_name) != 0)
		tmp_link = tmp_link->next;
	tmp_link->type_room = OUT;
}
