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

    i = sum_ascii(room->room_name) % TABLE_SIZE;
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

/*void		validate_link(t_lem_in *lem_in, t_link *link)
{
	t_link *compare;

	compare = lem_in->links;
	while (compare)
	{
		if (compare != link &&
			((!ft_strcmp(link->start->name, compare->start->name) &&
			!ft_strcmp(link->end->name, compare->end->name)) ||
			(!ft_strcmp(link->start->name, compare->end->name) &&
			!ft_strcmp(link->end->name, compare->start->name))))
			terminate(ERR_LINK_DUP);
		compare = compare->next;
	}
}*/
