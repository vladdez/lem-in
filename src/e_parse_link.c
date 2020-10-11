/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:01:00 by kysgramo          #+#    #+#             */
/*   Updated: 2020/10/09 20:07:15 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	add_link(t_node *link, char *toward)
{
	t_node	*tmp;

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
				break ;
			}
			tmp = tmp->next;
		}
	}
}

void	find_toward_room(t_hashtable *ht_rooms, char *toward, char *start)
{
	t_room	*tmp;
	int		i;

	i = sum_ascii(toward);
	if (ht_rooms->room[i] != NULL)
	{
		tmp = ht_rooms->room[i];
		while (tmp)
		{
			if (ft_strcmp(tmp->room_name, toward) == 0)
				return (add_link(tmp->link, start));
			tmp = tmp->next;
		}
		if (tmp == NULL)
			terminate(ERR_LINK_PARSING);
	}
	else
		terminate(ERR_LINK_PARSING);
}

void	find_start_room(t_hashtable *ht_rooms, char *start, char *toward)
{
	t_room	*tmp;
	int		i;

	i = sum_ascii(start);
	if (ht_rooms->room[i] != NULL)
	{
		tmp = ht_rooms->room[i];
		while (tmp)
		{
			if (ft_strcmp(tmp->room_name, start) == 0)
			{
				find_toward_room(ht_rooms, toward, start);
				return (add_link(tmp->link, toward));
			}
			tmp = tmp->next;
		}
		if (tmp->link->node != NULL)
			return ;
	}
	else
		terminate(ERR_LINK_PARSING);
}

void	create_link(t_lem_in *lem_in, char *str)
{
	char		*start;
	char		*toward;
	char		*d;
	int			dashes_number;

	d = str;
	dashes_number = count_dashes_in_imput(str);
	if (dashes_number > 1)
		start_toward_for_dashes_imput(lem_in, str);
	else if (dashes_number == 1)
	{
		d = ft_strchr(d, '-');
		if (!(start = ft_strsub(str, 0, d - str)))
			terminate(ERR_LINK_INIT);
		if (!(toward = ft_strsub(d + 1, 0, ft_strlen(d + 1))))
			terminate(ERR_LINK_INIT);
		find_start_room(lem_in->ht_rooms, start, toward);
	}
	else
		terminate(ERR_LINK_PARSING);
}

void	parse_link(t_lem_in *lem_in, int fd, t_line **input, t_line **tmp)
{
	if ((*tmp) == NULL)
		terminate(ERR_NO_LINKS);
	while ((*tmp) || ((*tmp) = read_line(input, fd)))
	{
		if (is_command((*tmp)->data) != COMMAND &&
				is_comment((*tmp)->data) != 1)
			create_link(lem_in, (*tmp)->data);
		(*tmp) = NULL;
		lem_in->edge_num++;
	}
	if (lem_in->start->link->node == NULL)
		terminate(ERR_NO_PATH);
}
