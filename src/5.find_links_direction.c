//
// Created by Ирина Деева on 13.08.2020.
//

#include "lem-in.h"

void MarkDirection(t_node *link, char *room_name)
{
    t_node *tmp;

    if (link->node == NULL)
    {
        link->node = room_name;
        link->next = NULL;
    }
    else
    {
        tmp = link;
        while (tmp)
        {
            if (tmp->next == NULL)
            {
                tmp->next = neighbour_init();
                tmp = tmp->next;
                tmp->node = room_name;
                break;
            }
            tmp = tmp->next;
        }
    }
}

void findLinkDirection(t_hashtable *ht_rooms)
{
    int i;
    t_node *tmp;
    t_room *tmp2;
    t_room *tmp3;

    i = 0;
    while (i < TABLE_SIZE)
    {
        if (ht_rooms->room[i] != NULL)
        {
            tmp2 = ht_rooms->room[i];
            while (tmp2)
            {
                if (ht_rooms->room[i]->link != NULL)
                {
                    tmp = ht_rooms->room[i]->link;
                    while (tmp)
                    {
                        tmp3 = FindRoomInHashtable(tmp->node,ht_rooms);
                        if (ht_rooms->room[i]->bfs_level > tmp3->bfs_level)
                            MarkDirection(ht_rooms->room[i]->incomingLinks, tmp3->room_name);
                        else
                            MarkDirection(ht_rooms->room[i]->outgoingLinks, tmp3->room_name);
                        tmp = tmp->next;
                    }
                }
                tmp2 = tmp2->next;
            }
        }
        i++;
    }
}





