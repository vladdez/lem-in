/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:38:11 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/01 20:38:21 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void		  validate_room(t_lem_in *lem_in, t_room *room)
{
    t_room *compare;

    compare = lem_in->rooms;
    while (compare)
    {
        if (compare != room && !ft_strcmp(compare->name, room->name))
            terminate(ERR_ROOM_NAME_DUP);
        if (compare != room && compare->x == room->x && compare->y == room->y)
            terminate(ERR_ROOM_COORDS_DUP);
        compare = compare->next;
    }
}

void		  validate_link(t_lem_in *lem_in, t_link *link)
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
}