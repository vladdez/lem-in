/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_turn_around2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 22:11:06 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 22:11:08 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	analyse_dup_links_not_on_the_way_but_neibours(t_path *path,
t_lem_in *lem_in)
{
	t_path *tmp;
	t_path *lagged_tmp;

	lagged_tmp = path;
	tmp = lagged_tmp->next;
	while (ft_strcmp(tmp->name, lem_in->end->room_name) != 0)
	{
		find_and_delete_dup_links(lagged_tmp, tmp, tmp->next,
		lem_in->ht_rooms);
		tmp = tmp->next;
	}
}

void	change_link_price(t_room *room, char *link_name, int link_typeroom)
{
	t_node *tmp;

	tmp = room->link;
	while (tmp)
	{
		if (ft_strcmp(tmp->node, link_name) == 0 &&
		tmp->type_room == link_typeroom)
			break ;
		tmp = tmp->next;
	}
	tmp->price == ONE ? (tmp->price = MINUS_ONE) : (tmp->price = ONE);
}

void	amend_links_in_direction_from_start(t_path *room,
t_path *link, t_hashtable *ht)
{
	t_room *tmp;

	tmp = find_room_with_type_in_hashtable(room->name, room->typeroom, ht);
	change_link_price(tmp, link->name, link->typeroom);
	change_link_direction(tmp, link->name, link->typeroom);
	if (check_condition_to_delete_dup_links(tmp->in_out, link->typeroom) == 1)
		delete_dup_link_in_both_room(tmp, link, ht);
}

/*
**	//анализ линков и удалени дублированных линков при повороте
*/

void	amend_links_in_direction_from_end(t_path *room,
t_path *link, t_hashtable *ht)
{
	t_room *tmp;

	tmp = find_room_with_type_in_hashtable(room->name, room->typeroom, ht);
	change_link_price(tmp, link->name, link->typeroom);
	change_link_direction2(tmp, link->name, link->typeroom);
}

void	turn_around_links(t_lem_in *lem_in, t_path *path)
{
	t_path *tmp;

	tmp = path;
	while (ft_strcmp(tmp->name, lem_in->end->room_name) != 0)
	{
		if (ft_strcmp(tmp->name, tmp->next->name) != 0)
		{
			amend_links_in_direction_from_start(tmp, tmp->next,
			lem_in->ht_rooms);
			amend_links_in_direction_from_end(tmp->next, tmp,
			lem_in->ht_rooms);
		}
		tmp = tmp->next;
	}
	analyse_dup_links_not_on_the_way_but_neibours(path, lem_in);
}
