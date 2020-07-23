
#include "lem-in.h"

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