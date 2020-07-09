/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 20:35:41 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/07 20:35:48 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	delete_link(t_lem_in *lem_in, t_link *link)
{
	t_link	*prev;
	t_link	*curr;

	curr = lem_in->links;
	prev = NULL;
	while (curr && curr != link)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev && curr)
		lem_in->links = curr->next;
	else if (curr)
		prev->next = curr->next;
	if (link->start->output_links > 0)
		link->start->output_links--;
	if (link->end->output_links > 0)
		link->end->output_links--;
	free(link);
}

void	check_links(t_lem_in *lem_in)
{
    t_link	*curr;
	t_link	*tmp;

	curr = lem_in->links;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		if (tmp->start->bfs_level == -1 || tmp->end->bfs_level == -1)
			delete_link(lem_in, tmp);
		if (tmp->start->bfs_level == tmp->end->bfs_level)
			delete_link(lem_in, tmp);
	}
} 