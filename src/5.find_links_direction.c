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
    t_node *LinksofCurrentRoom;
    t_room *CurrentRoomInHashTable;
    t_room *RoomFoundByLinkName;

    i = 0;
    while (i < TABLE_SIZE)
    {
        if (ht_rooms->room[i] != NULL)
        {
            CurrentRoomInHashTable = ht_rooms->room[i];
            while (CurrentRoomInHashTable)
            {
                if (CurrentRoomInHashTable->link != NULL && CurrentRoomInHashTable->bfs_level != -1)
                {
                    LinksofCurrentRoom = CurrentRoomInHashTable->link;
                    while (LinksofCurrentRoom)
                    {
                        RoomFoundByLinkName = FindRoomInHashtable(LinksofCurrentRoom->node, ht_rooms);
                        if (CurrentRoomInHashTable->bfs_level > RoomFoundByLinkName->bfs_level && RoomFoundByLinkName->bfs_level > -1)
                            MarkDirection(CurrentRoomInHashTable->incomingLinks, RoomFoundByLinkName->room_name);
                        if (CurrentRoomInHashTable->bfs_level < RoomFoundByLinkName->bfs_level && RoomFoundByLinkName->bfs_level > -1)
                            MarkDirection(CurrentRoomInHashTable->outgoingLinks, RoomFoundByLinkName->room_name);
                        LinksofCurrentRoom = LinksofCurrentRoom->next;
                    }
                }
                CurrentRoomInHashTable = CurrentRoomInHashTable->next;
            }
        }
        i++;
    }
}





