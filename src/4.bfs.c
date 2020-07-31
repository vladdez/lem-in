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
    if (!(q->room_name = malloc(sizeof(t_room *) * (room_num + 1))))
        terminate(ERR_ALLOCATION);
    while (i < room_num)
        q->room_name[i++] = NULL;
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
        q->room_name[q->from] = room->room_name;
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
    char *current_room_name;

    if (is_empty(q))
    {
        printf("Queue is empty");
        //current_room = NULL;
    }
    else
        {
            current_room_name = q->room_name[q->toward];
        q->toward++;
        if (q->toward > q->from)
            q->toward = q->from = -1;
    }
    return (current_room_name);
}

void	bfs(t_lem_in *lem_in)
{
    t_queue *q;
    int i;
    char *current_room_name;
    t_node *link;
    int level;

    level = 0;
    q = create_queue(lem_in->room_num);
    i = sum_ascii(lem_in->start->room_name) % TABLE_SIZE;
    lem_in->ht_rooms->room[i]->visit = 1;
    lem_in->ht_rooms->room[i]->bfs_level = level;
    enqueue(q, lem_in->ht_rooms->room[i], lem_in->room_num);
    while (!is_empty(q))
    {
        current_room_name = dequeue(q);
        i = sum_ascii(current_room_name) % TABLE_SIZE;
        link = lem_in->ht_rooms->room[i]->link;
        level++;
        while (link)
        {
            i =  sum_ascii(link->node) % TABLE_SIZE;
            if (lem_in->ht_rooms->room[i]->visit == UNVISISTED)
            {
                lem_in->ht_rooms->room[i]->visit = VISISTED;
                lem_in->ht_rooms->room[i]->bfs_level = level;
                enqueue(q, lem_in->ht_rooms->room[i], lem_in->room_num);
            }
            link = link->next;
        }
    }
}