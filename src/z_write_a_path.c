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
