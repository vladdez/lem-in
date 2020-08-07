/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:01:00 by kysgramo          #+#    #+#             */
/*   Updated: 2020/07/06 17:04:04 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"


void    add_link(t_node *link, char *toward)
{
    t_node *tmp;

    if (link->node == NULL)
    {
        link->node = toward;
        link->next = NULL;
    }
    else
    {
        tmp = link;
        while (tmp)
        {
            if (ft_strcmp(tmp->node, toward) == 0)
                terminate(ERR_LINK_PARSING);
            if (tmp->next == NULL)
            {
                tmp->next = neighbour_init();
                tmp = tmp->next;
                tmp->node = toward;
                break;
            }
            tmp = tmp->next;
        }
    }
}

void    find_toward(t_hashtable *ht_rooms, char *toward, char *start)
{
    t_room *tmp;
    int  i;

    i = sum_ascii(toward);
    if (ht_rooms->room[i] != NULL)
    {
        tmp = ht_rooms->room[i];
        while (tmp)
        {
            if (ft_strcmp(tmp->room_name, toward) == 0)
                return(add_link(tmp->link, start));
            tmp = tmp->next;
        }
        if (tmp == NULL)
            terminate(ERR_LINK_PARSING);
    }
    else
        terminate(ERR_LINK_PARSING);
}

void    find_start(t_hashtable *ht_rooms, char *start, char *toward)
{
    t_room *tmp;
    int  i;

    i = sum_ascii(start);
    if (ht_rooms->room[i] != NULL)
    {
        tmp = ht_rooms->room[i];
        while (tmp)
        {
            if (ft_strcmp(tmp->room_name, start) == 0)
            {
                find_toward(ht_rooms, toward, start);
                return(add_link(tmp->link, toward));
            }
            tmp = tmp->next;
        }
        if (tmp->link->node != NULL)
            return;
    }
    else
        terminate(ERR_LINK_PARSING);
}


void    create_link(t_lem_in *lem_in, char *str)
{
    char	*start;
    char	*toward;
    char	*d;

    d = str;
    if ((d = ft_strchr(d, '-')))
    {
        if (!(start = ft_strsub(str, 0, d - str)))
            terminate(ERR_LINK_INIT);
        if (!(toward = ft_strsub(d + 1, 0, ft_strlen(d + 1))))
            terminate(ERR_LINK_INIT);
        find_start(lem_in->ht_rooms, start, toward);
    }
    else
        terminate(ERR_LINK_PARSING);
}


void		parse_link(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp)
{
	while ((*tmp) || ((*tmp) = read_line(input, fd)))
	{
		if (is_command((*tmp) ->data) != COMMAND && is_comment((*tmp)->data) != 1)
		    create_link(lem_in, (*tmp)->data);
        (*tmp) = NULL;
	}
}
