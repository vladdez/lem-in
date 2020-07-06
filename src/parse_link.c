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

t_room		*find_room(t_lem_in *lem_in, char *str)
{
	t_room	*tmp;

	tmp = lem_in->rooms;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, str))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
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
		if (!(end = ft_strsub(d + 1, 0, ft_strlen(d) + 1)))
			terminate(ERR_LINK_INIT);
		start_room = find_room(lem_in, start);
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

void		parse_link(t_lem_in *lem_in, int fd, t_line **input, t_line **line)
{
	t_link	*link;

	while ((*line) || ((*line) = read_line(input, fd)))
	{
		if (is_command((*line)->data) != 1 && is_comment((*line)->data) != 1)
		{
			if (!(link = create_link(lem_in, (*line)->data)))
				terminate(ERR_LINK_PARSING);
			add_link(lem_in, link);
			validate_link(lem_in, link);
		}
		(*line) = NULL;
	}
}
