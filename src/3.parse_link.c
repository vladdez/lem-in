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

void		create_nei(t_room *room, char *to)
{
	t_nei	*tmp;
	t_nei	*mem;

    if (!(mem = (t_nei *)ft_memalloc(sizeof(t_nei))))
        terminate(ERR_LINK_INIT);
	mem->to = ft_strdup(to);
	mem->next = NULL;
	if (room->nei == NULL)
        room->nei = mem;
	else
    {
	    tmp = mem;
		tmp->next = room->nei;
        room->nei = tmp;
    }
}

void		find_room(t_room *room, char *from, char *to)
{
	int i;
	t_room *tmp;

	i = 0;
	if (!ft_strcmp(room->name, from))
		 create_nei(room, to);
	else
	{
		tmp = room;
		while (tmp)
		{
			if (!ft_strcmp(room->name, from))
			{
                create_nei(tmp, to);
                break;
			}
			else
				tmp = tmp->next;
		}
	}
}

void		use_link(t_lem_in *lem_in, char *str)
{
	char	*start;
	char	*end;
	int		i;
	char	*d;

	d = str;
	i = -1;
	if ((d = ft_strchr(d, '-')))
	{
		if (!(start = ft_strsub(str, 0, d - str)))
			terminate(ERR_LINK_INIT);
		if (!(end = ft_strsub(d + 1, 0, ft_strlen(d + 1))))
			terminate(ERR_LINK_INIT);
		if (ft_strchr(end, '-') != NULL)
			terminate(ERR_DASH_NAME);
		i = hash_fun(start);
		find_room(lem_in->hash_table[i], start, end);
		free(start);
		free(end);
	}
}

void		parse_link(t_lem_in *lem_in, int fd, t_line **input, t_line *tmp)
{
	while (tmp|| (tmp = read_line(input, fd)))
	{
		if (is_command(tmp->data) != 1 && is_comment(tmp->data) != 1)
		{
			use_link(lem_in, tmp->data);
			//validate_link(lem_in, link);
		}
		tmp = NULL;
	}
}
