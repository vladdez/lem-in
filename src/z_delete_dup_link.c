//
// Created by Brandy Hugo on 9/23/20.
//


#include "../inc/lem_in.h"


void	clean_and_free_dub_link(t_node *kill)
{
	free(kill->node);
	kill->next = NULL;
	free(kill);
}

void	detele_link_with_type(t_node *tmp_link, char *name_of_link_to_delete, int link_typeroom)
{
	t_node	*tmp_lagging_link;

	tmp_lagging_link = tmp_link;
	tmp_link = tmp_link->next;
	while (tmp_link)
	{
		if (ft_strcmp(tmp_link->node, name_of_link_to_delete) == 0 && tmp_link->type_room == link_typeroom)
			break;
		tmp_lagging_link = tmp_lagging_link->next;
		tmp_link = tmp_link->next;
	}
	tmp_lagging_link->next = tmp_link->next;
	clean_and_free_dub_link(tmp_link);
}


void    delete_dup_link(t_room *room, char *name_of_link_to_delete, int link_typeroom)
{
	t_node	*tmp_link;

	tmp_link = room->link;
	if (ft_strcmp(tmp_link->node, name_of_link_to_delete) == 0 && tmp_link->type_room == link_typeroom)
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

void    delete_dup_link_in_both_room(t_room *room, t_path *link, t_hashtable *ht)
{
	t_room *tmp;
	int type;

	type = IN_OUT;
	if (link->typeroom == IN)
		type = OUT;
	if (link->typeroom == OUT)
		type = IN;
	delete_dup_link(room, link->name, type);
	tmp = find_room_with_type_in_hashtable(link->name, type, ht);
	type = IN_OUT;
	if (room->in_out == IN)
		type = OUT;
	if (room->in_out == OUT)
		type = IN;
	delete_dup_link(tmp, room->room_name, type);
}

int    check_condition_to_delete_dup_links(int roomtype, int linktype)
{
	if (roomtype == IN_OUT && linktype != IN_OUT)
		return (1);
	if (roomtype != IN_OUT && linktype == IN_OUT)
		return (1);
	else
		return (0);
}