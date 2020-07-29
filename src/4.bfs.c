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

// Create a queue
t_queue *create_queue(int room_num)
{
    t_queue *q;

    int i;

    i = 0;
    if (!(q = malloc(sizeof(t_queue))))
        terminate(ERR_ALLOCATION);
    if (!(q->room = malloc(sizeof(t_room *) * (room_num + 1))))
        terminate(ERR_ALLOCATION);
    while (i < room_num)
        q->room[i++] = NULL;
    q->toward = -1;
    q->from = -1;
    return (q);
}


// Adding elements into queue
void enqueue(t_queue *q, t_room *room, int room_num)
{
    if (q->from == room_num - 1)
        printf("\nQueue is Full!!");
    else
        {
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
char *dequeue(t_queue *q)
{
    char *current_room;

    if (is_empty(q))
    {
        printf("Queue is empty");
        //current_room = NULL;
    }
    else
        {
            current_room = q->room[q->toward];
        q->toward++;
        if (q->toward > q->from)
            q->toward = q->from = -1;
    }
    return (current_room);
}

void	bfs(t_lem_in *lem_in)
{
    t_queue *q;
    int i;
    char *current_room;
    t_node *link;
    int level;

    level = 0;
    q = create_queue(lem_in->room_num);
    i = sum_ascii(lem_in->start->name) % TABLE_SIZE;
    lem_in->hash_table->room[i]->visit = 1;
    lem_in->hash_table->room[i]->bfs_level = level;
    enqueue(q, lem_in->hash_table->room[i], lem_in->room_num);
    while (!is_empty(q))
    {
        current_room = dequeue(q);
        i = sum_ascii(current_room) % TABLE_SIZE;
        link = lem_in->hash_table->room[i]->link;
        level++;
        while (link)
        {
            i =  sum_ascii(link->node) % TABLE_SIZE;
            if (lem_in->hash_table->room[i]->visit == 0)
            {
                lem_in->hash_table->room[i]->visit = 1;
                lem_in->hash_table->room[i]->bfs_level = level;
                enqueue(q, lem_in->hash_table->room[i], lem_in->room_num);
            }
            link = link->next;
        }
    }
}