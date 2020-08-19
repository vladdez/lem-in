//
// Created by Ирина Деева on 13.08.2020.
//

#include "lem-in.h"

void add_node(t_node *link, char *room_name)
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

int    compare_bfs_level(t_room *CurrentRoomInHashTable, t_hashtable *ht_rooms)
{
    t_node *LinksofCurrentRoom;
    t_room *RoomFoundByLinkName;
    int deadlock;

    deadlock = 0;
    LinksofCurrentRoom = CurrentRoomInHashTable->link;
    while (LinksofCurrentRoom)
    {
        RoomFoundByLinkName = FindRoomInHashtable(LinksofCurrentRoom->node, ht_rooms);
        if (CurrentRoomInHashTable->bfs_level > RoomFoundByLinkName->bfs_level)
            add_node(CurrentRoomInHashTable->incomingLinks, RoomFoundByLinkName->room_name);
        else
        {
            add_node(CurrentRoomInHashTable->outgoingLinks, RoomFoundByLinkName->room_name);
            deadlock++;
        }
        LinksofCurrentRoom = LinksofCurrentRoom->next;
    }
    return (deadlock);
}

void findLinkDirection(t_hashtable *ht_rooms)
{
    int     i;
    int     deadlock;
    t_room  *CurrentRoomInHashTable;
    t_node  *deadlock_room_name;

    i = 0;
    deadlock_room_name = neighbour_init();
    while (i < TABLE_SIZE)
    {
        if (ht_rooms->room[i] != NULL)
        {
            CurrentRoomInHashTable = ht_rooms->room[i];
            while (CurrentRoomInHashTable)
            {
                if (CurrentRoomInHashTable->link != NULL && CurrentRoomInHashTable->bfs_level != -1)
                {
                    deadlock = compare_bfs_level(CurrentRoomInHashTable, ht_rooms);
                    if (deadlock == 0 && CurrentRoomInHashTable->bfs_level != INT_MAX )
                        add_node(deadlock_room_name, CurrentRoomInHashTable->room_name);
                }
                CurrentRoomInHashTable = CurrentRoomInHashTable->next;
            }
        }
        i++;
    }
    clean_deadlock(deadlock_room_name, ht_rooms);
}





