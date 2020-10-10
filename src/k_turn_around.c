/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_turn_around.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:06:23 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 20:06:29 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	change_link_direction2(t_room *room, char *link_name, int link_typeroom)
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
	if (tmp->direction == BOTH_STREAM)
		tmp->direction = DOWNSTREAM;
	else if (tmp->direction == UPSTREAM)
		tmp->direction = DOWNSTREAM;
	else
		tmp->direction = UPSTREAM;
}

/*
** from START to next_room
*/

void	change_link_direction(t_room *room, char *link_name, int link_typeroom)
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
	if (tmp->direction == BOTH_STREAM)
		tmp->direction = UPSTREAM;
	else if (tmp->direction == UPSTREAM)
		tmp->direction = DOWNSTREAM;
	else
		tmp->direction = UPSTREAM;
}

void	delete_dup_links_not_on_the_way_but_neibours(t_room *room_tmp,
char *name_of_link_to_delete, t_hashtable *ht)
{
	t_room *tmp;

	delete_dup_link(room_tmp, name_of_link_to_delete, OUT);
	tmp = find_room_with_type_in_hashtable(name_of_link_to_delete, OUT, ht);
	delete_dup_link(tmp, room_tmp->room_name, room_tmp->in_out);
	change_link_direction(room_tmp, name_of_link_to_delete, IN);
	tmp = find_room_with_type_in_hashtable(name_of_link_to_delete, IN, ht);
	change_link_direction2(tmp, room_tmp->room_name, room_tmp->in_out);
}

void	find_and_delete_dup_links2(t_hashtable *ht, t_node *link_tmp2,
t_room *room_tmp, char *seeking_link)
{
	while (link_tmp2)
	{
		if (ft_strcmp(link_tmp2->node, seeking_link) == 0)
		{
			delete_dup_links_not_on_the_way_but_neibours(room_tmp,
			seeking_link, ht);
			break ;
		}
		link_tmp2 = link_tmp2->next;
	}
}

void	find_and_delete_dup_links(t_path *lagged, t_path *tmp,
t_path *next, t_hashtable *ht)
{
	t_room	*room_tmp;
	t_node	*link_tmp;
	t_node	*link_tmp2;
	char	*seeking_link;

	room_tmp = find_room_with_type_in_hashtable(tmp->name, tmp->typeroom, ht);
	link_tmp = room_tmp->link;
	while (link_tmp)
	{
		if (ft_strcmp(link_tmp->node, lagged->name) != 0 &&
		ft_strcmp(link_tmp->node, next->name) != 0)
		{
			seeking_link = link_tmp->node;
			link_tmp2 = link_tmp->next;
			find_and_delete_dup_links2(ht, link_tmp2, room_tmp, seeking_link);
		}
		link_tmp = link_tmp->next;
	}
}
