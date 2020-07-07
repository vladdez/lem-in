/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 19:01:31 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/07 18:04:01 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_queue	*create_q_elem(t_room *room)
{
	t_queue *q;

	if (!(q = (t_queue *)ft_memalloc(sizeof(t_queue *))))
		terminate(ERR_QUEUE_INIT);
	q->room = room;
	q->next = NULL;
	return (q);
}

void	add_q_elem(t_queue **q, t_queue	*elem)
{
	t_queue	*curr;

	if (q && *q)
	{
		curr = *q;
		while (curr->next)
			curr = curr->next;
		curr->next = elem;
	}
	else if (elem)
		*q = elem;
}

void	enqueue(t_lem_in *lem_in, t_queue **q, t_room *room)
{
	t_link *curr;

	curr = lem_in->links;
	while (curr)
	{
		if (curr->start == room)
		{
			if (curr->end->bfs_level == -1)
			{
				curr->end->bfs_level = room->bfs_level + 1;
				add_q_elem(q, create_q_elem(curr->end));
			}
		}
		else if (curr->end == room)
		{
			if (curr->end->bfs_level == -1)
			{
				curr->end->bfs_level = room->bfs_level + 1;
				add_q_elem(q, create_q_elem(curr->start));
			}
		}
		curr = curr->next;
	}
}

t_queue	*first_elem(t_queue **q)
{
	t_queue	*curr;

	curr = NULL;
	if (q && *q)
	{
		curr = *q;
		*q = (*q)->next;
	}
	return (curr);
}

void	bfs(t_lem_in *lem_in)
{
	t_queue *curr;
	t_queue *q;

	q = NULL;
	lem_in->start->bfs_level = 0;
	add_q_elem(&q, create_q_elem(lem_in->start));
	while(q)
	{
		curr = first_elem(&q);
		if (curr->room != lem_in->end)
		{
			enqueue(lem_in, &q, curr->room);
			lem_in->bfs_length = curr->room->bfs_level;          
		}
		else
			lem_in->end->bfs_level = 2147483647;
		free(curr);
	}
}
