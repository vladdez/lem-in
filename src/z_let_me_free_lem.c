/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_me_free_lem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kysgramo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 19:17:54 by kysgramo          #+#    #+#             */
/*   Updated: 2020/08/19 19:17:57 by kysgramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	free_links(t_node *sentenced)
{
	t_node *kill;

	if (sentenced)
		while (sentenced)
		{
			kill = sentenced;
			sentenced = sentenced->next;
			kill->node = NULL;
			free(kill);
			kill = NULL;
		}
}

void	free_ht(t_room **ht)
{
	int		i;
	t_room	*kill;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (ht[i] != NULL)
		{
			while (ht[i])
			{
				kill = ht[i];
				ht[i] = ht[i]->next;
				free(kill->room_name);
				free_node(&kill->link);
				free_links(kill->incoming_links);
				free_links(kill->outgoing_links);
				free(kill);
			}
		}
		i++;
	}
	free(ht);
}

void	free_coord(t_coordinate **input)
{
	t_coordinate	*curr;
	t_coordinate	*kill;

	curr = *input;
	while (curr)
	{
		kill = curr;
		curr = curr->next;
		free(kill->room_name);
		free(kill);
	}
	input = NULL;
}

void	free_lem_in(t_lem_in *lem_in, int fd)
{
	if (lem_in)
	{
		free_ht(lem_in->ht_rooms->room);
		free(lem_in->ht_rooms);
		free_coord(&(lem_in->coordinate));
		if (fd != 0)
			free_paths(lem_in->paths, lem_in->path_num);
		free(lem_in);
		(lem_in) = NULL;
	}
}

void	free_all(t_line *input, t_lem_in *lem_in,
int fd)
{
	free_input(input);
	free_lem_in(lem_in, fd);
}
