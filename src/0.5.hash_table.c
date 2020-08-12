
#include "lem-in.h"

int sum_ascii(char *room_name)
{
    int i;
    int sum;

    i = 0;
    sum = 0;
    while (room_name[i] != '\0')
    {
        sum += (int)(room_name[i]) * 49;
        i++;
    }
    return (sum % TABLE_SIZE);
}

t_room *FindRoomInHashtable(char *room_name, t_hashtable *ht_rooms)
{
    int  i;
    t_room *tmp;

    i = sum_ascii(room_name);
    tmp = ht_rooms->room[i];
    while (ft_strcmp(tmp->room_name, room_name) != 0)
        tmp = tmp->next;
    return (tmp);
}