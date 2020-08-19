//
// Created by Ирина Деева on 17.08.2020.
//

#include "lem-in.h"

void clean_deadlock(t_node *deadlock_room, t_hashtable *ht_rooms)
{
    t_node tmp;

    tmp = deadlock_room;
    ft_prinf("deadlocks/n");
    while(tmp)
    {
        ft_prinf("%s/n", deadlok_room->node);
        tmp = tmp->next;
    }
}