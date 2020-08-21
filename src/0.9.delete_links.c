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

#include "lem-in.h"

void	clean_and_free_link(t_node *kill)
{
	free(kill->node);
	kill->node = NULL;
	kill->next = NULL;
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

	tmp_link = room->incomingLinks;
	if (ft_strcmp(tmp_link->node, name_of_link_to_delete) == 0)
	{
		if (tmp_link->next == NULL)
			room->incomingLinks->node = NULL;
		else
			room->incomingLinks = tmp_link->next;
		return (room->incomingLinks);
	}
	else
		return (detele_link(tmp_link, name_of_link_to_delete));
}

t_node	*delete_outgoinglink(t_room *room, char *name_of_link_to_delete)
{
	t_node	*tmp_link;

	tmp_link = room->outgoingLinks;
	if (ft_strcmp(tmp_link->node, name_of_link_to_delete) == 0)
	{
		if (tmp_link->next == NULL)
			room->outgoingLinks->node = NULL;
		else
			room->outgoingLinks = tmp_link->next;
		return (room->outgoingLinks);
	}
	else
		return (detele_link(tmp_link, name_of_link_to_delete));
}
