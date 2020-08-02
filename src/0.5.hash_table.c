
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