/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.9.delete_links.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 12:16:14 by bhugo             #+#    #+#             */
/*   Updated: 2020/08/21 12:21:37 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	clean_and_free_link(t_node *kill)
{
	kill->node = NULL;
	kill->next = NULL;
	free(kill);
}

t_node	*detele_link(t_node *tmp_link, char *name_of_link_to_delete)
{
	t_node	*tmp_lagging_link;

	tmp_lagging_link = tmp_link;
	tmp_link = tmp_link->next;
	while (ft_strcmp(tmp_link->node, name_of_link_to_delete) != 0)
	{
		tmp_lagging_link = tmp_lagging_link->next;
		tmp_link = tmp_link->next;
	}
	tmp_lagging_link->next = tmp_link->next;
	return (tmp_lagging_link->next);
}

t_node	*delete_this_link(t_room *room, char *name_of_link_to_delete)
{
	t_node	*tmp_link;

	tmp_link = room->link;
	if (ft_strcmp(tmp_link->node, name_of_link_to_delete) == 0)
	{
		if (tmp_link->next == NULL)
			room->link->node = NULL;
		else
			room->link = tmp_link->next;
		return (room->link);
	}
	else
		return (detele_link(tmp_link, name_of_link_to_delete));
}

t_node	*delete_incominglink(t_room *room, char *name_of_link_to_delete)
{
	t_node	*tmp_link;

	tmp_link = room->incoming_links;
	if (ft_strcmp(tmp_link->node, name_of_link_to_delete) == 0)
	{
		if (tmp_link->next == NULL)
			room->incoming_links->node = NULL;
		else
			room->incoming_links = tmp_link->next;
		return (room->incoming_links);
	}
	else
		return (detele_link(tmp_link, name_of_link_to_delete));
}

t_node	*delete_outgoinglink(t_room *room, char *name_of_link_to_delete)
{
	t_node	*tmp_link;

	tmp_link = room->outgoing_links;
	if (ft_strcmp(tmp_link->node, name_of_link_to_delete) == 0)
	{
		if (tmp_link->next == NULL)
			room->outgoing_links->node = NULL;
		else
			room->outgoing_links = tmp_link->next;
		return (room->outgoing_links);
	}
	else
		return (detele_link(tmp_link, name_of_link_to_delete));
}
