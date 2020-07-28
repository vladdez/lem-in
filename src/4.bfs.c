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

/*t_queue	*create_q_elem(t_room *room)
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
}*/

// Create a queue
t_queue *create_queue(int room_num)
{
    t_queue *q;

    if (!(q = malloc(sizeof(t_queue)*(room_num + 1))))
        terminate(ERR_ALLOCATION);
    //q[room_num] = NULL;
    q->toward = -1;
    q->from = -1;
    return (q);
}


// Adding elements into queue
void enqueue(t_queue *q, t_room *room, int room_num)
{
    if (q->from == room_num - 1)
        printf("\nQueue is Full!!");
    else {
        if (q->toward == -1)
            q->toward = 0;
        q->from++;
        q->room[q->from] = room->name;
    }
}

// Check if the queue is empty
int is_empty(t_queue *q)
{
    if (q->from == -1)
        return 1;
    else
        return 0;
}

// Removing elements from queue
t_room *dequeue(t_queue *q)
{
    t_room *item;

    if (is_empty(q))
    {
        printf("Queue is empty");
        //item = -1;
    }
    else
        {
        //item = q->room[q->toward];
        q->toward++;
        if (q->toward > q->from)
        {
            printf("Resetting queue ");
            q->toward = q->from = -1;
        }
    }
    return item;
}

void	bfs(t_lem_in *lem_in)
{
    t_queue *q;
    int i;

    q = create_queue(lem_in->room_num);
    i = sum_ascii(lem_in->start->name) % TABLE_SIZE;
    lem_in->hash_table->room[i]->visit = 1;
    enqueue(q, lem_in->hash_table->room[i], lem_in->room_num);
    while (!is_empty(q))
    {

    }
}