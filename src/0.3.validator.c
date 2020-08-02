/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:38:11 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/06 17:03:10 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"


void    validate_name(t_hashtable *ht_rooms, t_room *room)
{
    int  i;
    t_room *compare;

    i = sum_ascii(room->room_name);
    compare = ht_rooms->room[i];
    while (compare)
    {
        if (compare != room && !ft_strcmp(compare->room_name, room->room_name))
            terminate(ERR_ROOM_NAME_DUP);
        compare = compare->next;
    }
}

void    validate_coordinate(t_coordinate *coordinate)
{
    t_coordinate *compare;

    compare = coordinate;
    while (compare->next)
        compare = compare->next;
    while (coordinate->next)
    {
        if (compare != coordinate && compare->x == coordinate->x && compare->y == coordinate->y)
            terminate(ERR_ROOM_COORDS_DUP);
        coordinate = coordinate->next;
    }
}

void		validate_room(t_lem_in *lem_in, t_room *room)
{

    validate_name(lem_in->ht_rooms, room);
    validate_coordinate(lem_in->coordinate);
}

int			iswhat(char *str)
{
	if 	(is_command(str) == 1)
		return (COMMAND);
	if (is_room(str) == 1)
		return (ROOM);
	if 	(is_comment(str) == COMMAND)
		return (3);
	else
		return (-1);
}
