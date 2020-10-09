/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_write_a_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:06:58 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 20:07:02 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_path	*put_belmon_ford_to_the_path(t_lem_in *lem_in, t_queue_bf *belmon_ford)
{
	t_path *tmp_path;
	t_path *point_path;
	t_room *tmp_room;

	tmp_path = create_one_path(lem_in->end);
	belmon_ford = belmon_ford->parrent;
	while (belmon_ford->parrent != NULL)
	{
		tmp_room = find_room_with_type_in_hashtable(belmon_ford->room_name,
		belmon_ford->type_room, lem_in->ht_rooms);
		point_path = create_one_path(tmp_room);
		point_path->typeroom = belmon_ford->type_room;
		point_path->next = tmp_path;
		tmp_path = point_path;
		belmon_ford = belmon_ford->parrent;
	}
	point_path = create_one_path(lem_in->start);
	point_path->next = tmp_path;
	tmp_path = point_path;
	return (tmp_path);
}

int		check_condition_to_delete_dup_links(int roomtype, int linktype)
{
	if (roomtype == IN_OUT && linktype != IN_OUT)
		return (1);
	if (roomtype != IN_OUT && linktype == IN_OUT)
		return (1);
	else
		return (0);
}

void	delete_dup_link_in_both_room(t_room *room, t_path *link,
t_hashtable *ht)
{
	if (room->in_out == IN_OUT)
		delete_dup_link_with_out_room(room, link, ht);
	if (room->in_out == OUT)
		delete_dup_link_with_in_room(room, link, ht);
}

void	delete_dup_link_with_in_room(t_room *room, t_path *link,
t_hashtable *ht)
{
	t_room *tmp;

	tmp = find_room_with_type_in_hashtable(room->room_name, IN, ht);
	delete_dup_link(tmp, link->name, link->typeroom);
	tmp = find_room_with_type_in_hashtable(link->name, link->typeroom, ht);
	delete_dup_link(tmp, room->room_name, IN);
}
