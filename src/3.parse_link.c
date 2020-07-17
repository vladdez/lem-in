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

t_link		*init_link(t_room *start, t_room *end)
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

t_room		find_room(t_room *hash_table, int room_num ,char *str)
{
    int i;
    struct s_room tmp;

    i = sum_ascii(str) % room_num;
    if (ft_strcmp(hash_table[i].name, str))
        return (hash_table[i]);
    else
    {
        while (tmp)
        {
            tmp = hash_table[i].next;
            if (ft_strcmp(hash_table[i].name, str))
                return (tmp);
            else
                tmp = tmp->next;
        }
        terminate(ERR_LINK_PARSING);
    }

}

t_link		*create_link(t_lem_in *lem_in, char *str)
{
	char	*start;
	char	*end;
	t_room	*start_room;
	t_room	*end_room;
	char	*d;

	d = str;
	if ((d = ft_strchr(d, '-')))
	{
		if (!(start = ft_strsub(str, 0, d - str)))
			terminate(ERR_LINK_INIT);
		if (!(end = ft_strsub(d + 1, 0, ft_strlen(d + 1))))
			terminate(ERR_LINK_INIT);
		start_room = find_room(lem_in->hash_table, lem_in->room_num, start);
		end_room = find_room(lem_in, end);
		free(start);
		free(end);
		if (start_room && end_room)
			return (init_link(start_room, end_room));
	}
	return (NULL);
}

void		add_link(t_lem_in *lem_in, t_link *link)
{
	t_link	*tmp;

	tmp = lem_in->links;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = link;
	}
	else
		lem_in->links = link;
}

void		parse_link(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp)
{
	t_link	*link;

	while (((*tmp) = read_line(input, fd)))
	{
		if (is_command((*tmp)->data) != 1 && is_comment((*tmp)->data) != 1)
		{
			if (!(link = create_link(lem_in, (*tmp)->data)))
				terminate(ERR_LINK_PARSING);
			add_link(lem_in, link);
			validate_link(lem_in, link);
		}
		(*tmp) = NULL;
	}
}
 // try