//
// Created by Ирина Деева on 13.08.2020.
//

#include "lem-in.h"

void cleanAndFreeLink(t_node *kill)
{
    free(kill->node);
    kill->node = NULL;
    free(kill);
    kill = NULL;
}


t_node *DeleteThisLink(t_room *room, char *nameOfLinkToDelete)
{
    t_node *tmpLink;
    t_node *tmpLaggingLink;

    tmpLink = room->link;
    if (ft_strcmp(tmpLink->node, nameOfLinkToDelete) == 0)
    {
        room->link = tmpLink->next;
        cleanAndFreeLink(tmpLink);
        return (room->link);
    }
    else
    {
        tmpLaggingLink = tmpLink;
        tmpLink = tmpLink->next;
        while(tmpLink)
        {
            if (ft_strcmp(tmpLink->node, nameOfLinkToDelete) == 0)
            {
                tmpLaggingLink->next = tmpLink->next;
                cleanAndFreeLink(tmpLink);
                return (tmpLaggingLink->next);
            }
            tmpLaggingLink = tmpLaggingLink->next;
            tmpLink = tmpLink->next;
        }
    }
}

void    deleteOutgoingLinksforEnd(t_room *EndRoom, t_hashtable *ht_rooms)
{
    t_node *tmpLinkOfEndRoom;
    t_room *tmpRoom;

    tmpLinkOfEndRoom = EndRoom->link;
    while (tmpLinkOfEndRoom)
    {
         tmpRoom = FindRoomInHashtable(tmpLinkOfEndRoom->node, ht_rooms);
         if (EndRoom->bfs_level < tmpRoom->bfs_level)
         {
             tmpLinkOfEndRoom = DeleteThisLink(EndRoom,tmpLinkOfEndRoom->node);
             DeleteThisLink(tmpRoom, EndRoom->room_name);
         }
         else
            tmpLinkOfEndRoom = tmpLinkOfEndRoom->next;
    }

}

void ImputCleaning(t_lem_in *lem_in)
{
    deleteOutgoingLinksforEnd(lem_in->end, lem_in->ht_rooms);
    lem_in->end->bfs_level = INT_MAX;
}

