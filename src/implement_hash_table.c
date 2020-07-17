
#include "lem-in.h"
t_room *clean_hash_table(t_room *hash_table, int num_room)
{
    int i;

    i = 0;
    while (num_room--)
    {
        hash_table[i].name = NULL;
        hash_table[i].x = -1;
        hash_table[i].y = -1;
        hash_table[i].bfs_level = -1;
        hash_table[i].input_links = -1;
        hash_table[i].output_links = -1;
        hash_table[i].next = NULL;
        i++;
    }
}

t_room *init_hash_table(int num_room)
{
    t_room *hash_table;
    int i;

    i = 0;
    if (!(hash_table = (t_room *)malloc(sizeof(hash_table) *  num_room)))
         terminate(ERR_ALLOCATION);
    clean_hash_table(hash_table, num_room);
    return(hash_table);
}

int count_rooms(t_room *start)
{
    t_room *tmp;
    int i;

    i = 1;
    tmp = start;
    while(tmp->next)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}

int invert_ascii(int i)
{
    return (i);
}

int sum_ascii(char *room_name)
{
    int i;
    int sum;

    i = 0;
    sum = 0;
    while (room_name[i] != '\0')
    {
        sum += invert_ascii(room_name[i]);
        i++;
    }
    return (sum);
}

t_room *create_hash_table(t_lem_in *lem_in)
{
    t_room *tmp;
    t_room *tmp2;
    t_room *tmp3;
    t_room *hash_table;
    int i;

    hash_table = NULL;
    lem_in->room_num = count_rooms(lem_in->start);
    hash_table = init_hash_table(lem_in->room_num);
    tmp = lem_in->start;
    while (tmp)
    {
        i = sum_ascii(tmp->name) % lem_in->room_num;
        tmp2 = tmp;                                   // этого колдовства не будет если сразу так сохранять команты после обработки комнаты
        tmp = tmp->next;                             // и этого тоже
        tmp2->next = NULL;                           //
        if (hash_table[i].name == NULL)
            hash_table[i] = *tmp2;
        else
        {
            *tmp3 = hash_table[i];                     // надо тестить на совпадаение индексов
            while (tmp3)
                tmp3 = tmp3->next;
            tmp3->next = tmp2;
        }
    }
    return (hash_table);
}