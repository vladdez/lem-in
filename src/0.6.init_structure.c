/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.6.init_structure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 17:19:52 by bhugo             #+#    #+#             */
/*   Updated: 2020/08/19 17:19:55 by bhugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_room		*create_room(t_coordinate *coordinate, char *tmp)
{
	t_room		*room;
	char		**words;

	if (!(words = ft_strsplit(tmp, ' ')))
		terminate(ERR_ROOM_INIT);
	if (!(room = (t_room *)malloc(sizeof(t_room))))
		terminate(ERR_ROOM_INIT);
	if (!(room->room_name = ft_strdup(words[0])))
		terminate(ERR_ROOM_INIT);
	write_coor(coordinate, words);
	room->visit = UNVISITED;
	room->visit2 = UNVISITED;
	room->bfs_level = -1;
	room->output_links = 0;
	room->input_links = 0;
	room->next = NULL;
	room->link = neighbour_init();
	room->outgoingLinks = neighbour_init();
	room->incomingLinks = neighbour_init();
	ft_strsplit_free(&words);
	return (room);
}

t_node	*neighbour_init(void)
{
	t_node *link;

	if (!(link = malloc(sizeof(t_node) * 1)))
		terminate(ERR_ALLOCATION);
	link->node = NULL;
	link->next = NULL;
	return (link);
}
