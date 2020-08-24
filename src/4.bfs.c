/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 19:01:31 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/20 16:59:06 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	enqueue(t_queue *q, t_room *room, int room_num)
{
	if (q->from == (room_num - 1))
		printf("\nQueue is Full!!");
	else
	{
		if (q->toward == -1)
			q->toward = 0;
		q->from++;
		q->room_name[q->from] = room->room_name;
	}
}

int		is_empty(t_queue *q)
{
	if (q->from == -1)
		return (1);
	else
		return (0);
}

char	*dequeue(t_queue *q)
{
	char	*current_room_name;

	current_room_name = NULL;
	if (is_empty(q))
		printf("Queue is empty");
	else
	{
		current_room_name = q->room_name[q->toward];
		q->toward++;
		if (q->toward > q->from)
		{
			q->toward = -1;
			q->from = -1;
		}
	}
	return (current_room_name);
}


void	handle_queue(t_lem_in *lem_in, t_queue *q, char *current_room_name)
{
	t_room	*current_room;
	int		level;
	t_node	*link;
	t_room	*tmp;

	current_room = find_room_in_hashtable(current_room_name, lem_in->ht_rooms);
	level = current_room->bfs_level + 1;
	link = find_room_links(current_room_name, lem_in->ht_rooms);
	while (link)
	{
		tmp = find_room_in_hashtable(link->node, lem_in->ht_rooms);
		if (tmp->visit == UNVISITED)
		{
			tmp->visit = VISITED;
			tmp->bfs_level = level;
			enqueue(q, tmp, lem_in->room_num);
		}
		link = link->next;
	}
}

t_queue	*bfs(t_lem_in *lem_in)
{
	t_queue	*q;
	char	*current_room_name;

	q = create_queue(lem_in->room_num);
	lem_in->start->visit = VISITED;
	lem_in->start->bfs_level = 0;
	enqueue(q, lem_in->start, lem_in->room_num);
	while (!is_empty(q))
	{
		current_room_name = dequeue(q);
		if (ft_strcmp(current_room_name, lem_in->end->room_name) != 0)
			handle_queue(lem_in, q, current_room_name);
	}
	lem_in->end->bfs_level = INT_MAX;
	return (q);
}

void	handle_queue2(t_lem_in *lem_in, t_queue *q, char *current_room_name)
{
	t_room	*current_room;
	int		level;
	t_node	*link;
	t_room	*tmp;

	current_room = find_room_in_hashtable(current_room_name, lem_in->ht_rooms);
	level = current_room->bfs_level2 + 1;
	link = find_room_links(current_room_name, lem_in->ht_rooms);
	while (link)
	{
		tmp = find_room_in_hashtable(link->node, lem_in->ht_rooms);
		if (tmp->visit3 == UNVISITED)
		{
			tmp->visit3 = VISITED;
			tmp->bfs_level2 = level;
			enqueue(q, tmp, lem_in->room_num);
		}
		link = link->next;
	}
}

t_queue	*bfs2(t_lem_in *lem_in)
{
	t_queue	*q;
	char	*current_room_name;

	q = create_queue(lem_in->room_num);
	lem_in->start->visit3 = VISITED;
	lem_in->start->bfs_level2 = 0;
	enqueue(q, lem_in->start, lem_in->room_num);
	while (!is_empty(q))
	{
		current_room_name = dequeue(q);
		if (ft_strcmp(current_room_name, lem_in->end->room_name) != 0)
			handle_queue2(lem_in, q, current_room_name);
	}
	lem_in->end->bfs_level = INT_MAX;
	return (q);
}