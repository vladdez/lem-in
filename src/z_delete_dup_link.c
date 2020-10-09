/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_delete_dup_link.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:09:07 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 20:09:18 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	clean_and_free_dub_link(t_node *kill)
{
	free(kill->node);
	kill->next = NULL;
	free(kill);
}

void	detele_link_with_type(t_node *tmp_link, char *name_of_link_to_delete,
int link_typeroom)
{
	t_node	*tmp_lagging_link;

	tmp_lagging_link = tmp_link;
	tmp_link = tmp_link->next;
	while (tmp_link)
	{
		if (ft_strcmp(tmp_link->node, name_of_link_to_delete) == 0 &&
		tmp_link->type_room == link_typeroom)
			break ;
		tmp_lagging_link = tmp_lagging_link->next;
		tmp_link = tmp_link->next;
	}
	tmp_lagging_link->next = tmp_link->next;
	clean_and_free_dub_link(tmp_link);
}

void	delete_dup_link(t_room *room, char *name_of_link_to_delete,
int link_typeroom)
{
	t_node	*tmp_link;

	tmp_link = room->link;
	if (ft_strcmp(tmp_link->node, name_of_link_to_delete) == 0 &&
	tmp_link->type_room == link_typeroom)
	{
		if (tmp_link->next == NULL)
			room->link->node = NULL;
		else
		{
			room->link = tmp_link->next;
			clean_and_free_dub_link(tmp_link);
		}
	}
	else
		detele_link_with_type(tmp_link, name_of_link_to_delete, link_typeroom);
}

int		define_room_type(int room_type)
{
	int type;

	type = IN_OUT;
	if (room_type == IN)
		type = OUT;
	if (room_type == OUT)
		type = IN;
	return (type);
}

void	delete_dup_link_with_out_room(t_room *room, t_path *link,
t_hashtable *ht)
{
	t_room	*tmp;
	int		roomtype_to_delete;

	roomtype_to_delete = define_room_type(link->typeroom);
	delete_dup_link(room, link->name, roomtype_to_delete);
	tmp = find_room_with_type_in_hashtable(link->name, roomtype_to_delete, ht);
	roomtype_to_delete = define_room_type(room->in_out);
	delete_dup_link(tmp, room->room_name, roomtype_to_delete);
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

/*
** находим дублера
** удаляем связь между  дублером и следующей комнатой
** удаляем связь между  дублером и следующей комнатой
** находим следующую команату
** удаляем у нее связь с дублером
*/

void	delete_dup_link_in_both_room(t_room *room, t_path *link,
t_hashtable *ht)
{
	if (room->in_out == IN_OUT)
		delete_dup_link_with_out_room(room, link, ht);
	if (room->in_out == OUT)
		delete_dup_link_with_in_room(room, link, ht);
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
