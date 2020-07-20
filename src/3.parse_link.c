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

static void		add_link(t_lem_in *lem_in, t_link *link)
{
	t_link	*current;

	current = lem_in->links;
	if (current)
	{
		while (current->next)
			current = current->next;
		current->next = link;
	}
	else
		lem_in->links = link;
}

static t_link	*init_link(t_room *start, t_room *end)
{
	t_link	*link;

	if (!(link = (t_link *)ft_memalloc(sizeof(t_link))))
		terminate(ERR_LINK_INIT);
	link->start = start;
	link->end = end;
	link->next = NULL;
	link->prev = NULL;
	return (link);
}

static t_link	*create_link(t_lem_in *lem_in, char *str)
{
	char	*dash;
	char	*start_name;
	char	*end_name;
	t_room	*start_room;
	t_room	*end_room;
	int		i;

	dash = str;
	while ((dash = ft_strchr(dash + 1, '-')))
	{
		if (!(start_name = ft_strsub(str, 0, dash - str)))
			terminate(ERR_LINK_INIT);
		if (!(end_name = ft_strsub(dash + 1, 0, ft_strlen(dash + 1))))
			terminate(ERR_LINK_INIT);
		i = hash_fun(start_name);
		start_room = find_room(lem_in->hash_table[i], start_name);
		i = hash_fun(end_name);
		end_room = find_room(lem_in->hash_table[i], end_name);
		free(start_name);
		free(end_name);
		if (start_room && end_room)
			return (init_link(start_room, end_room));
	}
	return (NULL);
}

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

void		find_room_nei(t_room *room, char *from, char *to)
{
	int i;
	t_room *tmp;
	
	if (room == NULL)
		terminate(ERR_NO_ROOM);
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
		find_room_nei(lem_in->hash_table[i], start, end);
		free(start);
		free(end);
	}
}

void		parse_link(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp)
{
	t_link	*link;

	while ((*tmp)|| ((*tmp) = read_line(input, fd)))
	{
		if (is_command((*tmp)->data) != 1 && is_comment((*tmp)->data) != 1)
		{
			use_link(lem_in, (*tmp)->data);
			if (!(link = create_link(lem_in, (*tmp)->data)))
				terminate(ERR_LINK_PARSING);
			add_link(lem_in, link);
			validate_link(lem_in, link);
		}
		(*tmp) = NULL;
	}
}
