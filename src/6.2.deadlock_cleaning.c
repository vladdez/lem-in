//
// Created by Ирина Деева on 17.08.2020.
//

#include "lem-in.h"

void find_links_to_deadlock(char *deadlock_name, t_hashtable *ht_rooms);

void    print_deadlock(t_node *deadlock_room)
{
    t_node *tmp;

    tmp = deadlock_room;
    ft_printf("deadlocks\n");
    while(tmp)
    {
        ft_printf("%s\n", tmp->node);
        tmp = tmp->next;
    }
    ft_printf("\n");
}

t_node  *delete_incominglink(t_room *room, char *nameOfLinkToDelete)
{
    t_node  *tmpLink;
    t_node  *tmpLaggingLink;

    tmpLink = room->incomingLinks;
    if (ft_strcmp(tmpLink->node, nameOfLinkToDelete) == 0)
    {
        if (tmpLink->next == NULL)
            room->incomingLinks->node = NULL;
        else
        {
            room->incomingLinks = tmpLink->next;
            //clean_and_free_link(tmpLink);
            //free(tmpLink);
        }
        return (room->incomingLinks);
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
                //clean_and_free_link(tmpLink);
                return (tmpLaggingLink->next);
            }
            else
            {
                tmpLaggingLink = tmpLaggingLink->next;
                tmpLink = tmpLink->next;
            }
        }
    }
}


t_node  *delete_outgoinglink(t_room *room, char *nameOfLinkToDelete)
{
    t_node  *tmpLink;
    t_node  *tmpLaggingLink;

    tmpLink = room->outgoingLinks;
    if (ft_strcmp(tmpLink->node, nameOfLinkToDelete) == 0)
    {
        if (tmpLink->next == NULL)
            room->outgoingLinks->node = NULL;
        else
        {
            room->outgoingLinks = tmpLink->next;
            //clean_and_free_link(tmpLink);
            //free(tmpLink);
        }
        return (room->outgoingLinks);
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
                //clean_and_free_link(tmpLink);
                //free(tmpLink);
                return (tmpLaggingLink->next);
            }
            else
            {
                tmpLaggingLink = tmpLaggingLink->next;
                tmpLink = tmpLink->next;
            }
        }
    }
}


void detele_deadlock_to_fork(char  *links_name, char *deadlock_name, t_hashtable *ht_rooms)
{
    t_room *deadlock_neighbour;

    deadlock_neighbour = FindRoomInHashtable(links_name, ht_rooms);
    delete_outgoinglink(deadlock_neighbour, deadlock_name);
    if (deadlock_neighbour->outgoingLinks->node == NULL)
        find_links_to_deadlock(deadlock_neighbour->room_name, ht_rooms);
}

void find_links_to_deadlock(char *deadlock_name, t_hashtable *ht_rooms)
{
    t_room *deadlock_room;
    t_node *incoming_links_in_deadlock_room;

    deadlock_room = FindRoomInHashtable(deadlock_name, ht_rooms);
    incoming_links_in_deadlock_room = deadlock_room->incomingLinks;
    while(incoming_links_in_deadlock_room != NULL && incoming_links_in_deadlock_room->node != NULL )
    {
        detele_deadlock_to_fork(incoming_links_in_deadlock_room->node, deadlock_name, ht_rooms);
        delete_incominglink(deadlock_room, incoming_links_in_deadlock_room->node);
        incoming_links_in_deadlock_room = incoming_links_in_deadlock_room->next;
    }
    deadlock_room->bfs_level = -1;
    //incoming_links_in_deadlock_room = deadlock_room->incomingLinks;
    //free_node(&incoming_links_in_deadlock_room);
    //deadlock_room->incomingLinks = NULL;
}

void clean_deadlock(t_node *deadlock_room_name, t_hashtable *ht_rooms)
{
    t_node *current_deadlock_name;

    print_deadlock(deadlock_room_name);
    current_deadlock_name = deadlock_room_name;
    while(current_deadlock_name && current_deadlock_name->node != NULL )
    {
        find_links_to_deadlock(current_deadlock_name->node, ht_rooms);
        current_deadlock_name = current_deadlock_name->next;
    }
    //free_node(&deadlock_room_name);
}